CC=g++ -std=c++11 -pthread
CFLAGS=-I.
DEPS = udp_low.hpp UDPStripControl.hpp ClockControl.hpp HeartControl.hpp StripAnimations.hpp MatrixControl.hpp pb_common.h pb_decode.h pb_encode.h pb.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

LEDControl:  main.o UDPStripControl.o  udp_low.o HeartControl.o ClockControl.o StripAnimations.o MatrixControl.o pb_common.o pb_decode.o pb_encode.o
	$(CC) -o LEDControl main.o UDPStripControl.o  -