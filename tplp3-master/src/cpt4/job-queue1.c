#include<malloc.h>
#include<pthread.h>

struct job{
	/* Link field for linked list.*/
	struct job* next;
	int dato;
};
/* A linked list of pending jobs.*/
struct job* job_queue;

/* Process queued jobs until the queue is empty.*/
void* thread_function (void* arg){
	while (job_queue != NULL) {
/* Get the next available job. */
	struct job* next_job = job_queue;
/* Remove this job from the list. */
	job_queue = job_queue->next;
/* Carry out the work. */
	printf("Procesando el dato %d\n", next_job->dato);
	/* Clean up. */
	free (next_job);
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
	pthread_t thread;
	pthread_create(&thread, NULL, &thread_function, NULL);
	pthread_join(thread, NULL);
	return 0;
}
