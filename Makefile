CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
PROGRAMMER = st-flash

CMSIS = ../CMSIS

LINKER_FILE = linker_script.ld

CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -nostdlib
CPPFLAGS = -DSTM32F411xE
CPPFLAGS += -I$(CMSIS)/Device/ST/STM32F4/Include
CPPFLAGS += -I$(CMSIS)/CMSIS/Core/Include
LDFLAGS = -T $(LINKER_FILE)

PROJECT = blink

all: clean elf

bin: elf
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

hex: elf
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex

elf: main.o startup.o system_stm32f4xx.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(PROJECT).elf
	@echo ""
	$(SIZE) $(PROJECT).elf
	@echo "   code   inted uninted   total"
	@echo ""

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

system_stm32f4xx.o: $(CMSIS)/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CMSIS)/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c -c

.PHONY: clean
clean:
	rm -f *.o $(PROJECT).elf $(PROJECT).bin $(PROJECT).hex

run: bin
	$(PROGRAMMER) write $(PROJECT).bin 0x800000
