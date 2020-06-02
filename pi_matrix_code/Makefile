CC=g++
CFLAGS= -I. -g
DEPS = messagedata.pb.h pb.h pb_common.h pb_decode.h pb_encode.h matrix.h communication.h

RGB_LIB_DISTRIBUTION=rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

%.o: %.c $(DEPS)
	$(CC) -I$(RGB_INCDIR) $(CFLAGS) -c -o $@ $<

%.o: %.cpp $(DEPS)
	$(CC) -I$(RGB_INCDIR) $(CFLAGS) -c -o $@ $<


PiMatrix: PiMatrix messagedata.pb.o pb_common.o pb_encode.o pb_decode.o communication.o matrix.o main.o  $(RGB_LIBRARY)
	$(CC) $(CFLAGS) -o PiMatrix messagedata.pb.o pb_common.o pb_encode.o pb_decode.o communication.o matrix.o  main.o  $(LDFLAGS)


$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

clean:
	rm -f messagedata.pb.o pb_common.o pb_encode.o pb_decode.o communication.o main.o 

FORCE:
.PHONY: FORCE