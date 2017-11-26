# Specify Compiler
CC=gcc

#Specify options for compiler
CFLAGS=-c -Wall

program: SantaSync.o MethodHeaders.h ElfMethods.c SantaMethods.c ReindeerMethods.c 
		$(CC) SantaSync.c  MethodHeaders.h ElfMethods.c SantaMethods.c ReindeerMethods.c -pthread -lm -o program

SantaSync: SantaSync.c
		$(CC) $(CFLAGS) SantaSync.c

methodHeaders: MethodHeaders.h
		$(CC) $(CFLAGS) MethodHeaders.h

ReindeerMethods: ReindeerMethods.c
		$(CC) $(CFLAGS) ReindeerHeaders.c

ElfMethods: ElfMethods.c
		$(CC) $(CFLAGS) ElfMethods.c

SantaMethods: SantaMethods.c
		$(CC) $(CFLAGS) SantaMethods.c

clean: 
		rm -rf *o program 