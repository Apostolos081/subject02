#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define READ 0
#define WRITE 1
#define NUM_CLIENTS 5
#define NUM_PRODUCTS 20
#define MAX_ORDERS 10
#define <fuctionsbodies.cpp>
#define <functionsdeclarions.cpp>


typedef struct products{
	char description[50];
	int price;
	int item_count;
}products;

products catalog[NUM_PRODUCTS];


int main(void){
	 initialize_catalog();
	
	 initialize_pipes_and_pid();
	
	 check_pipes();
	
	 client_working();
	
	 server_working();
	
	
	return 0;
	
}
