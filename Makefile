CC=gcc
CFLAGS=-I.

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

tp2virtual: tp2virtual.o page_table.o fifo.o rand.o 
	$(CC) -o tp2virtual tp2virtual.o page_table.o fifo.o rand.o
