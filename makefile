OBJS = thread.o hashmap.o
CC = gcc
CFLAGS = -g -Wall

thread: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f thread *.o
