CC = gcc
CFLAGS = -g -Wall 

test: test.c nmenu.o
	$(CC) $(CFLAGS) -o test test.c nmenu.o -lncurses

nmenu.o: nmenu.c
	$(CC) $(CFLAGS) -o nmenu.o -c nmenu.c -lncurses

clean:
	rm -rf test nmenu.o
