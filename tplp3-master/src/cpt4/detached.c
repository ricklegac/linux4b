#include<pthread.h>
#include<stdio.h>

void* thread_function(void* thread_arg){
	int i;
	for(i = 0; i <= 10000; i++)
		printf("no se programar ");
}

int main(){
	int i;
	pthread_attr_t attr;
	pthread_t thread;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thread, &attr, &thread_function, NULL);
	pthread_attr_destroy(&attr);
	for(i = 0; i <= 10000; i++)
		printf("cachicho hizo todo");
	return 0;
}
