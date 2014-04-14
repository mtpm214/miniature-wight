//file to test how to implement threads
#include "thread.h"

//int sem_init(sem_t *sem, 0, unsigned int value); 
//int sem_wait(sem_t *s); /* P(s) */
//int sem_post(sem_t *s);

#define NUMTHREADS 1000

int main(int  argc, char **argv){  
    return 0;
}

void init_order_buf(order_buffer *ob, int buf_size){
    *ob->buf = calloc(buf_size, sizeof(order));
    ob->size = buf_size;
    ob->currOrder = *ob->buf;
    sem_init(&ob->mutex, 0, 1);
    sem_init(&ob->emptySlots, 0, buf_size);
    sem_init(&ob->availableOrders, 0, 0);
}

void kill_order_buf(order_buffer *ob);

//after order is processed it is not needed in the order_buffer anymore
void free_order(order *tempo){
    free(tempo->categ_name);
    free(tempo->customer_name);
    free(tempo->book_name);
    free(tempo);
}

void *fillNewOrde();
void *processOrder(void *args);

