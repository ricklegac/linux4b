#include<pthread.h>
#include<stdio.h>
/*Calculamos sucesivamente números primos. Retornamos el N-ésimo número primo, donde N es un valor apuntado por *ARG*/
void* compute_prime(void* arg){
	int candidate = 2;
	int n = *((int *) arg);
	while(1){
		int factor;
		int is_prime = 1;
		/*Verificamos si es un número primo a través de divisiones sucesivas*/
 		for(factor = 2; factor < candidate; ++factor){
			if(candidate % factor == 0){
				is_prime = 0;
				break;
			}
		}
		if(is_prime){
			if(--n == 0)
				/*Retorna el número*/
					return (void*) candidate;
		}
		++candidate;
	}
	return NULL;
}

int main(){
	pthread_t thread;
	int which_prime = 5000;
	int prime;
	/*Comenzamos el calculo, hasta el número primo 5000*/
	pthread_create(&thread, NULL, &compute_prime, &which_prime);
	/*Hacemos otra cosa paralelamente*/
	int i;
	for(i = 0; i <= 10000; i++)
		printf("x");
	/*Esperamos que el hilo complete su tarea*/
	pthread_join(thread, (void*) &prime);
	/*Imprimimos el número calculado*/
	printf("El número primo %d es %d.\n", which_prime, prime);
	return 0;
}
