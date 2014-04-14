#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXBUFSIZE 10

typedef struct info_t{
    char * categ_name; //which thread to go to
    char * customer_name; //for customer funds
    char * book_name; //for price of book
}order;

typedef struct orders_struct{
	order **buf;
	int size; //should not exceed MAXBUFSIZE
	//order *front;
	//order *rear;
	order *currOrder;
	sem_t mutex;
    sem_t emptySlots;
    sem_t availableOrders; 
}order_buffer;

void init_order_buf(order_buffer *sb, int size);
void kill_order_buf(order_buffer *sb);
void free_order(order *tempo);
void *fillNewOrde();
void *processOrder(void *args);
