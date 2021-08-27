#include <pthread.h>
#include<stdio.h>
void do_work();
int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;
void initialize_flag(){
	/*Inicializamos el mutex y la variable de condición*/
	pthread_mutex_init (&thread_flag_mutex, NULL);
	pthread_cond_init (&thread_flag_cv, NULL);
	/*Inicializamos la bandera*/
	thread_flag = 0;
}

/*Llamamos repetidamente a do_Work si la bandera está en 1, la bloqueamos en caso contrario*/
void* thread_function (void* thread_arg){
	void* ptr;
	while(1){
		/*Bloqueamos el mutex antes de acceder a la bandera*/
		pthread_mutex_lock (&thread_flag_mutex);
		while (!thread_flag)
			/*La bandera está en 0, esperamos una señal que indique que el valor cambió.
			Cuando llegue la señal el hilo se desbloquea, itera, y vuelve a revisar la bandera*/
			pthread_cond_wait (&thread_flag_cv, &thread_flag_mutex);
		pthread_mutex_unlock (&thread_flag_mutex);
		do_work ();
		pthread_exit(ptr);
	}
	return NULL;
}

void set_thread_flag (int flag_value){
	pthread_mutex_lock (&thread_flag_mutex);
	thread_flag = flag_value;
	pthread_cond_signal (&thread_flag_cv);
	pthread_mutex_unlock (&thread_flag_mutex);
}

void do_work(){
	printf("El hilo recibió la señal de que el valor cambió\n");
	set_thread_flag(0);
}

int main(){
	set_thread_flag(1);
	pthread_t thread1;
	pthread_create(&thread1, NULL, &thread_function, NULL);
	pthread_join(thread1, NULL);
}
