#ifndef HASHMAP_H
#define HASHMAP_H

//credit for the hashmap backend is given to UTHash from: http://troydhanson.github.io/uthash/
#include "uthash.h"
#include "customer.h"
#include <pthread.h>


//holds the key and a LinkedList of Indexes, from index.c
//UT_hash_handle is what uthash uses to create our hashmap
struct threadHash{
	char * category_key;
	pthread_t TID;
	UT_hash_handle hh;
};
typedef struct threadHash * threadHashPtr;

struct customerHash{
	int customer_key;
	customer customer_info;
	UT_hash_handle hh;
};
typedef struct customerHash * customerHashPtr;
/*
 * Used to clear the hash and free all memory when caller is done with it
 */
void clearCustomerHash(customerHashPtr *);

void clearThreadHash(threadHashPtr *);


int addCategory(char *, pthread_t, threadHashPtr *);

int addCustomer(int, customer, customerHashPtr *);



/*
 * A get function for the hashmap
 * Returns the linked list of indexes given a certain key (a word)
 */
pthread_t getThreadID(char *, threadHashPtr *);

customer getCustomer(int, customerHashPtr *);



#endif