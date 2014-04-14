#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "hashmap.h"

#define MAXBUFSIZE 10

//change hashmap.h in order to fit this pa
//need a hashmap for category name to tid
//need a hashmap for customer name to customer info
typedef struct info_t{
    char * categ_name; //which thread to go to
    char * customer_name; //for customer funds
    char * book_name; //for price of book
}orderInfo;

typedef struct orders_struct{
	orderInfo **buf;
	int size; //should not exceed MAXBUFSIZE
	//orderInfo *front;
	//orderInfo *rear;
	orderInfo *currOrder;
	sem_t mutex;
    sem_t emptySlots;
    sem_t availableOrders; 
}orderBuffer;

typedef struct arg_t{
	hashPtr thread_table; //TEMP: CHANGE HASH TYPE
    hashPtr customer_table; //TEMP: CHANGE HASH TYPE
	hashPtr book_table; //TEMP: CHANGE HASH TYPE
	orderBuffer orders_to_process;
}order;

//sets up everything so that buffer is able to process sales
void setup();

//initiates a buffer to the specified size
void init_order_buf(orderBuffer *ob, int size);

//deletes all orders from a buffer, in case something goes wrong
void kill_order_buf(orderBuffer *ob);

//deletes order from buffer after it has been processed
void free_order(order *tempo);

void *fillNewOrde(void *args);

//struct order will be passed as an argument in order to process the order
void *processOrder(void *args);
