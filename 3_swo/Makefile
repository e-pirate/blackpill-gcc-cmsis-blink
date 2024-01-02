CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
MD5SUM=md5sum
ST-FLASH=st-flash
ST-TRACE=st-trace
F_CPU_MHZ=48

CMSIS=../../CMSIS

LINKER_FILE=stm32f411xe.ld

CFLAGS=-std=c99 -Wall -Werror
CFLAGS+=-O1 -fdce -ffunction-sections -fdata-sections# Optimize for unused code
CFLAGS+=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mabi=aapcs -mfpu=fpv4-sp-d16 -mthumb-interwork
CFLAGS+=-specs=nano.specs
CFLAGS+=-DSTM32F411xE
CFLAGS+=-I.
CFLAGS+=-I$(CMSIS)/CMSIS/Core/Include
CFLAGS+=-I$(CMSIS)/Device/ST/STM32F4/Include
LDFLAGS=-T $(LINKER_FILE) -Wl,--fatal-warnings -Wl,--no-warn-rwx-segments -Wl,--gc-sections -Wl,--print-memory-usage# -u _printf_float

ifdef EXTRA_CFLAGS
CFLAGS+=${EXTRA_CFLAGS}
endif
ifdef EXTRA_LDFLAGS
CFLAGS+=${EXTRA_LDFLAGS}
endif

PROJECT=blink

all: clean elf

bin: all
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

hex: all
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex

elf: startup_stm32f411xx.o system_stm32f4xx.o syscalls.o swo.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(PROJECT).elf
	@echo ""
	$(MD5SUM) $(PROJECT).elf

main.o: main.c
	$(CC) $(CFLAGS) -c $^ 

startup_stm32f411xx.o: startup_stm32f411xx.c
	$(CC) $(CFLAGS) -c $^

system_stm32f4xx.o: $(CMSIS)/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) -c $^

syscalls.o: syscalls.c
	$(CC) $(CFLAGS) -c $^

swo.o: swo.c
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	rm -f *.o $(PROJECT).elf $(PROJECT).bin $(PROJECT).hex

.PHONY: run
run: bin
	$(ST-FLASH) --reset write $(PROJECT).bin 0x8000000
	$(ST-TRACE) --clock=$(F_CPU_MHZ) --verbose=0
