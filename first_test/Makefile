SRCPATH=../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src
HPATH=../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/inc
CM3PATH=../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3
LINKPATH=../STM32F10x_StdPeriph_Lib_V3.5.0/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210B-EVAL

STARTPATH=../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO

default: compile compile2 compile3 link convert stflash

compile:
	arm-none-eabi-gcc -Wall -mcpu=cortex-m3 -mlittle-endian -mthumb -mthumb-interwork $(SRCPATH)/stm32f10x_rcc.c $(SRCPATH)/stm32f10x_flash.c $(SRCPATH)/stm32f10x_gpio.c $(SRCPATH)/misc.c -I $(HPATH)/ -I $(CM3PATH)/DeviceSupport/ST/STM32F10x/ -I $(CM3PATH)/CoreSupport/ -I/usr/lib/gcc/arm-none-eabi/4.8.2/include/ -DSTM32F103 -Os -c main.c

compile2:
	arm-none-eabi-gcc -Wall -mcpu=cortex-m3 -mlittle-endian -mthumb -mthumb-interwork $(SRCPATH)/stm32f10x_rcc.c $(SRCPATH)/stm32f10x_flash.c $(SRCPATH)/stm32f10x_gpio.c $(SRCPATH)/misc.c -I $(HPATH)/ -I $(CM3PATH)/DeviceSupport/ST/STM32F10x/ -I $(CM3PATH)/CoreSupport/ -I/usr/lib/gcc/arm-none-eabi/4.8.2/include/ -DSTM32F103 -Os -c startup_stm32f10x_md.s

compile3:
	arm-none-eabi-gcc -Wall -mcpu=cortex-m3 -mlittle-endian -mthumb -mthumb-interwork $(SRCPATH)/stm32f10x_rcc.c $(SRCPATH)/stm32f10x_flash.c $(SRCPATH)/stm32f10x_gpio.c $(SRCPATH)/misc.c -I $(HPATH)/ -I $(CM3PATH)/DeviceSupport/ST/STM32F10x/ -I $(CM3PATH)/CoreSupport/ -I/usr/lib/gcc/arm-none-eabi/4.8.2/include/ -DSTM32F103 -Os -c system_stm32f10x.c

link:
	arm-none-eabi-gcc -mcpu=cortex-m3 -mlittle-endian -mthumb -mthumb-interwork -DSTM32F103 -T$(LINKPATH)/stm32_flash.ld -Wl,--gc-sections startup_stm32f10x_md.o system_stm32f10x.o main.o stm32f10x_flash.o stm32f10x_gpio.o misc.o stm32f10x_rcc.o  -o main.elf

convert:
	arm-none-eabi-objcopy -S -O binary main.elf main.bin

stflash:
	st-flash write main.bin 0x8000000

clean:
	rm -rf *.o *.elf *.hex *.bin

