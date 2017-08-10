CC = g++
CFLAGS = -Wall -std=c++11
LFLAGS = -lntl -lgmp
OBJS = misc.o

all: keygen enc dec clean

#keygen: keygen.o $(OBJS) 
	#$(CC) $(CFLAGS) keygen.o $(OBJS) $(LFLAGS) -o keygen

keygen: keygen.cxx misc.cxx
	$(CC) $(CFLAGS) keygen.cxx misc.cxx $(LFLAGS) -o keygen

enc: enc.cxx misc.cxx
	$(CC) $(CFLAGS) enc.cxx misc.cxx $(LFLAGS) -o enc

dec: dec.cxx
	$(CC) $(CFLAGS) dec.cxx $(LFLAGS) -o dec

clean: 
	rm *.o *~
