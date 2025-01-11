void initialize_catalog(){
	for(int i=0; i < NUM_PRODUCTS; i++){
		sprintf(catalog[i].description, "Poduct %d", i);
		catalog[i].price = (i+1) * 5.0;
		catalog[i].item_count = 2;
	}
}

void initialize_pipes_and_pid(){
	int pid;
	int pipe_server_to_client[2];
	int pipe_client_to_server[2];
}

void check_pipes(){
	if (pipe(pipe_server_to_client) == -1 || pipe(pipe_client_to_server) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void client_working(){
	for(int i=0; i < NUM_CLIENTS; i++){
		int pid = fork();
		
		if(pid < 0){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		if(pid == 0){
			float total = 0.0;
			int succesful_orders = 0;
			int failed_orders = 0;
			close(pipe_server_to_client[WRITE]);
			close(pipe_client_to_server[READ]);
			
			srand(time(NULL)+ i);
			for(int j=0; j<MAX_ORDERS;j++){
				int product_description = rand() % MAX_PRODUCTS;
			
				write(pipe_client_to_server[WRITE], &product_description,sizeof(product_description));
				char response[100];
				read(pipe_server_to_client[READ],response,sizeof(response));
				printf("Client %d received response: %s\n",i,response);
				if(strcmp(response," Order succesfull") == 0 ){
					total += catalog[i].price;
					succesful_orders++;
				}
				else{
					failed_orders++;
					printf("Client %d: products unavailable ,request failed");
				}
				
				sleep(1);
			}
			if(succesful_orders == 10){
				printf("Client %d:Purchase complete,your total is %.2f euro",i,total);
				
			}
			close(pipe_client_to_server[WRITE]);
			close(pipe_server_to_client[READ]);
			exit(EXIT_SUCCESS);		
		}
	}
	
	close(pipe_server_to_clinet[WRITE]);
	close(pipe_client_to_server[READ]);
	
	void print_results(failed_orders,succesfull_orders,total);
}


void server_working(){
	for(int i = 0; i < NUM_CLIENTS; i++){
		int product_id;
		int succesfull_requests = 0;
		int failed_requests = 0;
		if(read(pipe_server_to_client[READ],&product_id,sizeof(int))>0){
			succesfull_requests++;
			char response[100];
			if(product_id>=0 && product_id<=20){
				if(catalog[product_id].item_count>0){
					catalog[product_id].item_count--;
					sprintf(response,"Order successful");
				}
				else{
					sprintf(response,"Order failed");
				}
			}
			else{
				sprintf(response,"Invalid product ID");
			}
			write(pipe_client_to_server[WRITE],response,sizeof(response));
		}
		else{
			failed_requests++;
		}
	
	}
	close(pipe_server_to_client[READ]);
	close(pipe_client_to_server[WRITE]);
}

void print_results(int failed_orders,int succesfull_orders,int total){
	printf("%d requests were made, where %d succeeded and %d failed",succesfull_requests+failed_requests,succesfull_requests,failed_requests);
	printf("%d products were requested, where %d products were bought, totaling %.2f euros",succesful_orders+failed_orders,succesful_orders,total);
}
