CFLAGS+=-Wall -I../lib 
LDFLAGS+=-L../lib 

.PHONY: all clean

all: chipcap2

chipcap2: chipcap2.o
	$(CC) $(LDFLAGS) chipcap2.o -o chipcap2

chipcap2.o: chipcap2.c
	$(CC) $(CFLAGS) -c chipcap2.c

clean:
	rm *.o chipcap2
