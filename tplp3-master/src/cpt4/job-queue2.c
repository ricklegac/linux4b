#include<malloc.h>
#include<pthread.h>

struct job{
	/*Puntero a la siguiente tarea*/
	struct job* next;
	int dato;
};
/*Lista enlazada de las tareas pendientes.*/
struct job* job_queue;
/* Mutex para proteger job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
/* Procesar las tareas de la cola hasta que esté vacía*/
void* thread_function(void* arg){
	while(1){
		struct job* next_job;
		/* Bloqueamos el mutex. */
		pthread_mutex_lock (&job_queue_mutex);
		/* Ahora es seguro verificar si la cola está vacía. */
		if (job_queue == NULL)
			next_job = NULL;
		else{
			/* Tomamos la siguiente tarea disponible. */
			next_job = job_queue;
			/* Lo sacamos de la lista*/
			job_queue = job_queue->next;
		}
		/*Desbloqueamos el mutex*/
		pthread_mutex_unlock (&job_queue_mutex);
		/*La cola está vacía?Entonces terminamos*/
		if (next_job == NULL)
			break;
		/*Sino continuamos trabajando*/
		printf("Procesando el dato %d\n", next_job->dato);
		free(next_job);		
	}
	return NULL;
}

int main(){
	//job_queue = NULL;
	int i = 0;
	for(i = 0; i < 10; i++){
		struct job *x = (struct job*) malloc(sizeof(struct job));
		x->dato = i;
	//	printf("%d", x->dato);
		x->next = job_queue;
		job_queue = x;	
	}
	pthread_t thread1;
	pthread_create(&thread1, NULL, &thread_function, NULL);
	pthread_join(thread1, NULL);
	return 0;
}
