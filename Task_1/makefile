target: all

all: main

main: readVirus.o
	gcc -m32 -g -o main readVirus.o


readVirus.o: readVirus.c
	gcc -m32 -g -o readVirus readVirus.c

clean:
	rm *.o readVirus
