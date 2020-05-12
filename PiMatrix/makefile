CC=g++ -std=c++11 -pthread
CFLAGS=-I.
DEPS = 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

PiMatrix:  main.o 
	$(CC) -o PiMatrix main.o 