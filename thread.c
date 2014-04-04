//file to test how to implement threads
#include <stdio.h>
#include <pthread.h>

#define NUMTHREADS 1000

void *processCategory(void *args);

typedef struct category_t{
	char * categ_name;
	//more things that deal with the category
	//use this struct to pass multiple arguments to thread function
}CATEGORY;

int main(int  argc, char **argv){
	int i;
	//char *categories[NUMTHREADS] = {"ACCOUNTING101", "SPORTS101", "MATH300"};
	pthread_t tid[NUMTHREADS];

	printf("THREADS\n");
	for(i=0; i<NUMTHREADS; i++){
		 //pthread_create(&(tid[i]), NULL, processCategory, categories[i]);
		 pthread_create(&(tid[i]), NULL, processCategory, i);
	}
	for(i=0; i<NUMTHREADS; i++){
		pthread_join(tid[i], NULL);
	}
	printf("COUNTER\n");
	for(i=0; i<NUMTHREADS; i++){
		printf("Testing counter: %d\n", i);
	}
	
	
	return 0;
}

void *processCategory(void *args){
	//printf("This category deals with: %s, my tid is: %d\n", (char *) args, (int) pthread_self());
	printf("Testing thread order: %d\n", (int) args);
	return NULL;
}

