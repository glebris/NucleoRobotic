all:
	arm-none-eabi-gcc -Wall -mcpu=cortex-m3 -mlittle-endian -mthumb -mthumb-interwork -I../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/ -I../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/CoreSupport/ -I/usr/lib/gcc/arm-none-eabi/4.8.2/include/ -DSTM32F103 -Os -c main.c -o main.o

clean:
	rm -rf *.o
