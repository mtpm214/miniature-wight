#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "hashmap.h"

#define MAXBUFSIZE 10

typedef struct info_t{
    int customer_id; //for customer funds
    char *book_name; //for price of book
    float bookprice;
}orderInfo;

typedef struct orders_struct{
	orderInfo **buf;
	customerHashPtr customer_table; //TEMP: CHANGE HASH TYPE
	threadHashPtr thread_table; //TEMP: CHANGE HASH TYPE
	int size; //should not exceed MAXBUFSIZE
	int front;
	int rear;
	//orderInfo *currOrder;
	sem_t mutex;
    sem_t emptySlots;
    sem_t availableOrders; 
}orderBuffer;

//sets up everything so that buffer is able to process sales
void setup();

//initiates a buffer to the specified size
void init_order_buf(orderBuffer *ob, int buf_size, customerHashPtr customer_db, threadHashPtr t_db);

//deletes all orders from a buffer, in case something goes wrong
void kill_order_buf(orderBuffer *ob);

//deletes order from buffer after it has been processed
void free_order(orderBuffer *ob, orderInfo *order);

void *fillNewOrder(void *args);

//struct order will be passed as an argument in order to process the order
void *processOrder(void *args);

void writeReport(FILE *opf);
