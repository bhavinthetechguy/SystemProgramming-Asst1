all: memgrind.c mymalloc.c mymalloc.h
	gcc -o program memgrind.c mymalloc.c
clean:
	rm program