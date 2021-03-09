CC=gcc
CFLAGS=-I.

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

tp2virtual: tp2virtual.o page_table.o vector.o fifo.o lru.o segunda_chance.o rand.o 
	$(CC) -o tp2virtual tp2virtual.o page_table.o vector.o fifo.o lru.o segunda_chance.o rand.o

clean:
	rm *.o tp2virtual
