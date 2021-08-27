/*Ejemplo de creación de hilos*/
#include<pthread.h>
#include<stdio.h>

/*imprime x en stderr*/
void* print_xs(void* unused){
	while(1)
		fputc('x', stderr);	
	return NULL;
}

int main(){
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &print_xs, NULL);
	while(1)
		fputc('o', stderr);
	return 0;
}

