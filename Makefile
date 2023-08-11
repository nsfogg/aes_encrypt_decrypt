CC = gcc
CFLAGS = -Wall -std=c99 -g

all: encrypt decrypt
fieldTest: fieldTest
aesTest: aesTest

encrypt: encrypt.o io.o field.o aes.o
	gcc encrypt.o io.o field.o aes.o -o encrypt

decrypt: decrypt.o io.o field.o aes.o
	gcc decrypt.o io.o field.o aes.o -o decrypt

fieldTest: fieldTest.o field.o
	gcc fieldTest.o field.o -o fieldTest

aesTest: aesTest.o field.o aes.o
	gcc aesTest.o field.o aes.o -o aesTest

encrypt.o: encrypt.c io.h field.h aes.h
decrypt.o: decrypt.c io.h field.h aes.h
io.o: io.c io.h field.h
aes.o: aes.c aes.h field.h
field.o: field.c field.h
fieldTest.o: fieldTest.c field.h
aesTest.o: aesTest.c field.h aes.h

clean:
	rm -f encrypt.o decrypt.o io.o field.o aes.o
	rm -f encrypt decrypt
	rm -f output.txt