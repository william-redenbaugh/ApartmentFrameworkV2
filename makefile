CC=g++ -std=c++11 -pthread
CFLAGS=-I.
DEPS = udp_low.hpp UDPStripControl.hpp ClockControl.hpp HeartControl.hpp StripAnimations.hpp MatrixControl.hpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

LEDControl:  main.o UDPStripControl.o  udp_low.o HeartControl.o ClockControl.o StripAnimations.o MatrixControl.o 
	$(CC) -o LEDControl main.o UDPStripControl.o  udp_low.o HeartControl.o ClockControl.o StripAnimations.o MatrixControl.o 