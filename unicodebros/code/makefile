OBJS	= CPU6502.o CPUBus.o Emulator.o helper.o main.o Memory.o Nesrom.o PPU2C02.o PPUBus.o Controller.o APU.o
SOURCE	= CPU6502.cpp CPUBus.cpp Emulator.cpp helper.cpp main.cpp Memory.cpp Nesrom.cpp PPU2C02.cpp PPUBus.cpp Controller.cpp APU.cpp
HEADER	= CPU6502.h CPUBus.h Emulator.h Memory.h Nesrom.h PPU2C02.h PPUBus.h Controller.h APU.h
OUT	= mario
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -L/usr/X11/lib -lX11 #-lsfml-audio -lsfml-system -L../portaudio/lib/.libs ../portaudio/lib/.libs/libportaudio.a -lportaudio -lrt -lm -lasound -ljack -pthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

CPU6502.o: CPU6502.cpp
	$(CC) $(FLAGS) CPU6502.cpp

CPUBus.o: CPUBus.cpp
	$(CC) $(FLAGS) CPUBus.cpp

Emulator.o: Emulator.cpp
	$(CC) $(FLAGS) Emulator.cpp

helper.o: helper.cpp
	$(CC) $(FLAGS) helper.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

Memory.o: Memory.cpp
	$(CC) $(FLAGS) Memory.cpp

Memoryppu.o: Memoryppu.cpp
	$(CC) $(FLAGS) Memoryppu.cpp

Nesrom.o: Nesrom.cpp
	$(CC) $(FLAGS) Nesrom.cpp

PPU2C02.o: PPU2C02.cpp
	$(CC) $(FLAGS) PPU2C02.cpp

PPUBus.o: PPUBus.cpp
	$(CC) $(FLAGS) PPUBus.cpp

Controller.o: Controller.cpp
	$(CC) $(FLAGS) Controller.cpp

APU.o: APU.cpp
	$(CC) $(FLAGS) APU.cpp

clean:
	rm -f $(OBJS) $(OUT)
