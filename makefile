OBJS = thread.o
CC = gcc
CFLAGS = -g -Wall

thread: thread.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f thread *.o
