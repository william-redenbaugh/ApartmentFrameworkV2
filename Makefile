CC=g++
CFLAGS= -I. -g
LDFLAGS+= -lrt -lm -lpthread
DEPS = ClockControl.h HeartControl.h MatrixControl.h messagedata.pb.h pb_decode.h pb_encode.h pb.h status.pb.h hsv_rgb_conv.hpp

%.o: %.c $(DEPS)
	$(CC) -I $(CFLAGS) -c -o $@ $<

%.o: %.cpp $(DEPS)
	$(CC) -I $(CFLAGS) -c -o $@ $<

PiFramework: PiFramework pb_common.o pb_decode.o pb_encode.o messagedata.pb.o MatrixControl.o HeartControl.o ClockControl.o hsv_rgb_conv.o main.o 
	$(CC) $(CFLAGS) -o PiFramework pb_common.o pb_decode.o pb_encode.o messagedata.pb.o UDPStripControl.o udp_low.o StripAnimations.o MatrixControl.o HeartControl.o ClockControl.o hsv_rgb_conv.o main.o  $(LDFLAGS)

clean:
	rm -f pb_common.o pb_decode.o pb_encode.o messagedata.pb.o MatrixControl.o HeartControl.o ClockControl.o status.pb.o hsv_rgb_conv.o main.o 

FORCE:
	.PHONY: FORCE