#include<pthread.h>
#include<stdio.h>
void set_thread_flag (int flag_value);

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag (){
	pthread_mutex_init (&thread_flag_mutex, NULL);
	thread_flag = 0;
}

/*Llamamos repetidamente a do_work mientras que thread_flag esté 1*/
void* thread_function(void* thread_Arg){
	void *ptr;
	while(1){
		int flag_is_set;
		/*Protegemos la bandera con un mutex*/
		pthread_mutex_lock (&thread_flag_mutex);
		flag_is_set = thread_flag;
		pthread_mutex_unlock (&thread_flag_mutex);
		if(flag_is_set){
			printf("La bandera > 0, el hilo realiza trabajo\n");
			set_thread_flag(0);
			pthread_exit(ptr);
		}
	}
	return NULL;
}

void set_thread_flag (int flag_value){
	/*Protegemos la bandera con un mutex*/
	pthread_mutex_lock (&thread_flag_mutex);
	thread_flag = flag_value;
	pthread_mutex_unlock (&thread_flag_mutex);
}

int main(){
	set_thread_flag(1);
	pthread_t thread1;
	pthread_create(&thread1, NULL, &thread_function, NULL);
	pthread_join(thread1, NULL);
}
