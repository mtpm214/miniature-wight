//file to test how to implement threads
#include "thread.h"

//int sem_init(sem_t *sem, 0, unsigned int value); 
//int sem_wait(sem_t *s); /* P(s) */
//int sem_post(sem_t *s); /* V(s) */

//for testing
//#define NUMTHREADS 1000
long getFileSize(FILE *fp){
    long fileSize;
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);

    return fileSize;
}

int main(int  argc, char **argv){ 
    if(argc != 4){
        printf("Illegal number of args.\n");
        printf("Exiting.\n");
        exit(1);
    }else{
        FILE *order_fp;
        char *db_file = argv[1];
        char *order_file = argv[2];
        char *categ_file = argv[3];
        threadHashPtr threadHash_t = NULL;
        customerHashPtr customerHash_t = NULL;
        setup(db_file, order_file, categ_file, threadHash_t, customerHash_t);
        
        if((order_fp = fopen(orderFile, "r")) == NULL){
            perror("Error trying to open orders file\n");
            printf("Program terminated\n");
            exit(1)
        }
        else{
            orderBuffer *order_buffer;
            void init_order_buf(order_buffer, MAXBUFSIZE, customerHash_t, threadHash_t);

            //pthread_t tid[NUMCATEGORIES];
            //for(i=0; i<NUMCATEGORIES; i++){
            //  pthread_create(&tid[i], NULL, fillNewOrder, order_fp);
            //  pthread_create(&tid[i], NULL, processOrder, NULL);
            //}
            //
            ////for(i=0; i<NUMCATEGORIES; i++){
            //  pthread_join(tid[i], NULL);
            //  pthread_join(tid[i], NULL);
            //}
            
        }
        return 0;
    }

    
}

void setup(char *dbFile, char *orderFile, char *categoriesFile, threadHashPtr t_hash, customerHashPtr c_hash){
    // parse file
    FILE *db_fp; // database.txt
     // orders.txt
    FILE *categories_fp; // categories.txt 

    if((db_fp = fopen(dbFile, "r")) == NULL){
        perror("Error trying to open database file\n");
        printf("Program terminated\n");
        exit(1)
    }
    else{
        long fileSize = getFileSize(db_fp);
        char buffer[fileSize];
        TokenizerT *tk;
        //char *data; // string read from tokenizer
        char *name, *address, *state, *zip;
        int customer_id;
        float customer_funds;
        customer * newCustomer;

        if(fileSize == 0){
            printf("File given was empty, please input another file.\n");
            printf("Program Exiting\n");
            exit(1);
        }

        while(fgets(buffer, fileSize, db_fp) != NULL){
            tk = TKCreate("|", buffer);

            while((name = TKGetNextToken(tk)) != NULL){
                customer_id = atoi(TKGetNextToken(tk));
                customer_funds = atof(TKGetNextToken(tk));
                address = TKGetNextToken(tk);
                state = TKGetNextToken(tk);
                zip = TKGetNextToken(tk);

                newCustomer = (customer *) malloc(sizeof(customer));
                newCustomer->name = name;
                newCustomer->address = address;
                newCustomer->state = state;
                newCustomer->zip = zip;
                newCustomer->balance = customer_funds;

                //customer_id = ((data = TKGetNextToken(tk)) != NULL) ? (atoi(data)) : (0);

                addCustomer(customer_id, newCustomer, &c_hash);
            }
        }
        fclose(db_fp);
        //addCustomer(int customerID, customer newCustomer, customerHashPtr *customerHash)
    }
    if((categories_fp = fopen(categoriesFile, "r")) == NULL){
        perror("Error trying to open categories file\n");
        printf("Program terminated\n");
        exit(1)
    }else{
        pthread_t tid;
        pthread_create();
    }

           
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
void *addNewOrder(void *args){
    //this is the one you need to do
    // Don't tell me what to do boy
    orderBuffer *

    return NULL; //temporary
}

//use wrapper around the critical sections of the code
//where the thread needs mutual exclusive access to the address
void *processOrder(void *args){
    //to make working a little easier
    //check if I have access to the buffer
    //orderBuffer *orders = (orderBuffer *) args;
    orderInfo oinf;
    int index;
    int c_id;
    char *b_name;
    float price;
    customer c_info;

    //wait for orders to become available
    sem_wait(&order_buffer->availableOrders);

    //beggin of mutual exclusion to buffer
    sem_wait(&order_buffer->mutex);
    index = (++order_buffer->front)%(orders->size);
    oinf = (*order_buffer->buf)[index];
    c_id = oinf.customer_id;
    b_name = oinf.book_name;
    price = oinf.bookprice;
    c_info = getCustomer(c_id, &order_buffer->customer_table);

    sem_post(&orders->mutex);
    //end of mutual exclusion to buffer

    //announce that there is another empty slot
    sem_post(&orders->emptySlots);

    return NULL; //temporary
}

