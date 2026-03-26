CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: cipher

cipher: tester.o cr.o
	$(CC) $(CFLAGS) -o cipher tester.o cr.o

tester.o: tester.c
	$(CC) $(CFLAGS) -c tester.c -o tester.o

cr.o: cipher.c
	$(CC) $(CFLAGS) -c cipher.c -o cr.o

clean:
	rm -f cipher *.o
