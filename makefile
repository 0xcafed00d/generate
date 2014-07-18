 
CC=clang++
CFLAGS=-c -Wall -std=c++11 -fexceptions

main: main.o
	$(CC) -o main main.o

main.o: main.cpp range.h generate.h
	$(CC) $(CFLAGS) main.cpp

run: main
	./main

clean: 
	rm *.o
	rm main



