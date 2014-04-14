OBJS = thread.o hashmap.o tokenizer.o
CC = gcc
CFLAGS = -g -Wall

thread: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

thread.o: thread.c thread.h
	$(CC) $(CFLAGS) -c $<

hashmap.o: hashmap.c hashmap.h customer.h
	$(CC) $(CFLAGS) -c $<

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CFLAGS) -c $<
	
.PHONY: clean
clean:
	rm -f thread *.o
