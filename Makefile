CC=gcc
CFLAGS=-I.
OUTPUT=vernamXOR

build: main.o vector.o input_helper.o file_reader.o vernam.o
	$(CC) main.o vector.o input_helper.o vernam.o file_reader.o -o $(OUTPUT)

main.o: main.c
	$(CC) -c main.c

timeutil.o: timeutil.c timeutil.h
	$(CC) -c timeutil.c

vector.o: vector.c vector.h
	$(CC) -c vector.c

vernam.o: vernam.c vernam.h
	$(CC) -c vernam.c

file_reader.o: file_reader.c file_reader.h
	$(CC) -c file_reader.c

clean:
	rm *.o $(OUTPUT)
