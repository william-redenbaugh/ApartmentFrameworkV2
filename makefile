CC=g++
CFLAGS=-I.
DEPS = udp_low.hpp UDPStripControl.hpp ClockControl.hpp HeartControl.hpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

LEDControl:  main.o UDPStripControl.o  udp_low.o HeartControl.o ClockControl.o
	$(CC) -o LEDControl main.o UDPStripControl.o  udp_low.o HeartControl.o ClockControl.o