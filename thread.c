//file to test how to implement threads
#include "thread.h"

//int sem_init(sem_t *sem, 0, unsigned int value); 
//int sem_wait(sem_t *s); /* P(s) */
//int sem_post(sem_t *s); /* V(s) */

//for testing
//#define NUMTHREADS 1000

int main(int  argc, char **argv){  
    return 0;
}

void setup(){
    //you also need to do this one
    //initialize customer table (c_id (int) to customer info)
}    //initialize thread table (category to thread id)}

//following books example
//change hashPtr 
void init_order_buf(orderBuffer *ob, int buf_size, customerHashPtr customer_db, threadHashPtr t_db){
    *ob->buf = calloc(buf_size, sizeof(orderInfo));
    ob->customer_table = customer_db;
    ob->thread_table = t_db;
    ob->successfulSales = SLCreate(compareCustomer, destroyCustomer);
    ob->rejectedSales = SLCreate(compareCustomer, destroyCustomer);
    ob->size = buf_size;
    ob->front = ob->rear = 0;
    //ob->currOrder = *ob->buf;
    sem_init(&ob->mutex, 0, 1);
    sem_init(&ob->emptySlots, 0, buf_size);
    sem_init(&ob->availableOrders, 0, 0);
}

//clear the entire order buffer
//use this if an unexpected error occurs
void kill_order_buf(orderBuffer *ob){
}

//after order is processed it is not needed in the order_buffer anymore
void free_order(orderBuffer *ob, orderInfo *order){
}

//use wrapper around the critical sections of the code
//where the thread needs mutual exclusive access to the address
void *fillNewOrder(void *args){
    //this is the one you need to do
    return NULL; //temporary
}

//use wrapper around the critical sections of the code
//where the thread needs mutual exclusive access to the address
void *processOrder(void *args){
   //to make working a little easier
    orderBuffer *orders = (orderBuffer *) args;
    orderInfo oinf;
    int index;
    int c_id;
    char *b_name;
    float price;
    customer c_info;

    //wait for orders to become available
    sem_wait(&orders->availableOrders);

    //beggin of mutual exclusion to buffer
    sem_wait(&orders->mutex);
    index = (++orders->front)%(orders->size);
    oinf = (*orders->buf)[index];
    c_id = oinf.customer_id;
    b_name = oinf.book_name;
    price = oinf.bookprice;
    c_info = getCustomer(c_id, &orders->customer_table);

    sem_post(&orders->mutex);
    //end of mutual exclusion to buffer

    //announce that there is another empty slot
    sem_post(&orders->emptySlots);

    return NULL; //temporary
}

