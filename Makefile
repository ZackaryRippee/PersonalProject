



CC = g++

CFLAGS = -g -Wall -Wextra

TARGET = test

default: all

all: main.o
	$(CC) $(CFlags) -o $(TARGET) main.o

main.o:
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) $(TARGET) *.o *~
