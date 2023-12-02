CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
PROGRAMMER = st-flash

CFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -nostdlib
CPPFLAGS=-DSTM32F410Rx \
				 -Ivendor/CMSIS/Device/ST/STM32F4/Include \
				 -Ivendor/CMSIS/CMSIS/Core/Include

LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE)

PROJECT = blink
BINARY = $(PROJECT).elf

all: $(BINARY)

$(BINARY): main.o startup.o system_stm32f4xx.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(BINARY)
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex

main.o: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c -c

startup.o: startup.c
	$(CC) $(CFLAGS) $(CPPFLAGS) startup.c -c

system_stm32f4xx.o: vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c -c

.PHONY: clean
clean:
	rm -f *.o $(PROJECT).elf $(PROJECT).bin $(PROJECT).hex

run: $(BINARY)
	$(PROGRAMMER) write $(PROJECT).bin 0x800000
