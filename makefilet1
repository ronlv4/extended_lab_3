all: main

main: utils.h readVirus.o printVirus.o
	gcc -g -m32 -Wall -o main utils.h readVirus.o printVirus.o main.c

readVirus.o: utils.h readVirus.c
	gcc -g -m32 -nostartfiles -Wall -o readVirus.o -e readVirus utils.h readVirus.c
printVirus.o: utils.h printVirus.c
	gcc -g -m32 -nostartfiles -Wall -o printVirus.o -e printVirus printVirus.c utils.h

clean:
	rm -f *.o main
