#ifndef THREAD_H
#define THREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "hashmap.h"
//#include "sorted-list.h"
//#include "sales.h"

#define MAXBUFSIZE 10

//MAYBE MAKE SEPARATE FILES, ONE THAT DEALS WITH PROCESSING AND THE OTHER ONE THAT DEALS WITH THE SALES
typedef struct info_t{
     int customer_id; //for customer funds
     char *book_name; //for price of book
     float bookprice;
 }orderInfo;



typedef struct orders_struct{
	orderInfo **buf;
	customerHashPtr customer_table;
	threadHashPtr thread_table;
	SortedListPtr successfulSales;
	SortedListPtr rejectedOrders;
	SortedList
	int size; //should not exceed MAXBUFSIZE
	int front;
	int rear;
	//orderInfo *currOrder;
	sem_t mutex;
    sem_t emptySlots;
    sem_t availableOrders; 
}orderBuffer;

//sets up everything so that buffer is able to process sales
void setup(char *dbFile, char *orderFile, char *categoriesFile, threadHashPtr t_hash, customerHashPtr c_hash);

//initiates a buffer to the specified size
void init_order_buf(orderBuffer *ob, int buf_size, customerHashPtr customer_db, threadHashPtr t_db);

//deletes all orders from a buffer, in case something goes wrong
void kill_order_buf(orderBuffer *ob);

//deletes order from buffer after it has been processed
void free_order(orderBuffer *ob, orderInfo *order);

void *addNewOrder(void *args);

//struct order will be passed as an argument in order to process the order
void *processOrder(void *args);

#endif
