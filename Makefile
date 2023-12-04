CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
PROGRAMMER = st-flash

CMSIS = ../CMSIS

LINKER_FILE = linker_script.ld

CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -nostdlib
#CFLAGS += -fdata-sections -ffunction-sections # optimize for unused code
CFLAGS += -DSTM32F411xE
CFLAGS += -I.
CFLAGS += -I$(CMSIS)/Device/ST/STM32F4/Include
CFLAGS += -I$(CMSIS)/CMSIS/Core/Include
LDFLAGS = -T $(LINKER_FILE)

PROJECT = blink

all: clean elf

bin: elf
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

hex: elf
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex

elf: startup.o system_stm32f4xx.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(PROJECT).elf
	@echo ""
	$(SIZE) $(PROJECT).elf
	@echo "   code   inted uninted   total"
	@echo ""

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

startup.o: startup.c
	$(CC) $(CFLAGS) -c startup.c

system_stm32f4xx.o: $(CMSIS)/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) -c $(CMSIS)/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c

.PHONY: clean
clean:
	rm -f *.o $(PROJECT).elf $(PROJECT).bin $(PROJECT).hex

run: bin
	$(PROGRAMMER) write $(PROJECT).bin 0x800000
