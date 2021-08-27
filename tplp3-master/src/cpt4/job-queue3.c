#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>

struct job{
	/*Puntero a la siguiente tarea*/
	struct job* next;
	int dato;
};
/*Lista enlazada de las tareas pendientes.*/
struct job* job_queue;
/* Mutex para proteger job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/*Un semáforo para contar la cantidad de tareas en la cola*/
sem_t job_queue_count;

/*Inicializamos la cola*/
void initialize_job_queue ()	{
/*La cola está inicialmente vacía. */
	job_queue = NULL;
/* Inicializamos el semáforo.*/
	sem_init (&job_queue_count, 0, 0);
}

/* Procesamos las tareas de la cola hasta que esté vacía*/
void* thread_function(void* arg){
	while(1){
		struct job* next_job;
		/*Esperamos en el semaforo. Si es un número positivo,
		indica que la cola no está vacía y se decrementa el contador en 1
		Si la cola está vacía, la bloqueamos hasta que llegue una nueva tarea*/
		sem_wait (&job_queue_count);
		/*Bloqueamos el mutex*/
		pthread_mutex_lock (&job_queue_mutex);
		/*Gracias al semáforo sabemos que la cola no está vacía*/
		next_job = job_queue;
		job_queue = job_queue->next;
		/*Desbloqueamos el mutex*/
		pthread_mutex_unlock (&job_queue_mutex);
		printf("Procesando el dato %d\n", next_job->dato);
		free(next_job);
	}
}

/*Añadimos nuevas tareas a la cola*/
void enqueue_job(int x){
	struct job* new_job;
	new_job = (struct job*) malloc (sizeof (struct job));
	new_job->dato = x;
	/*Bloqueamos el mutex antes de acceder a la cola*/
	pthread_mutex_lock (&job_queue_mutex);
	new_job->next = job_queue;
	job_queue = new_job;
	/*Indicamos que hay una tarea disponible. Si hay hilos esperando en el semáforo
	uno se desbloqueará y tomará la tarea*/
	sem_post (&job_queue_count);
	/*Desbloqueamos el mutex*/
	pthread_mutex_unlock (&job_queue_mutex);
}
void* thread_function2(void* arg){
	int i;	
	for(i = 0; i < 10; i++){
		enqueue_job(i);
	}
}
int main(){
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread2, NULL, &thread_function2, NULL);
	pthread_join(thread2, NULL);
	pthread_create(&thread1, NULL, &thread_function, NULL);
	printf("El hilo seguirá esperando la llegada de tareas, presione CTRL + C para terminar\n");
	pthread_join(thread1, NULL);
	return 0;
}
