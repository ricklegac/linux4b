#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};
/*Obtenemos el id del semáforo y le asignamos una dirección de memoria*/
int binary_semaphore_allocation (key_t key, int sem_flags){
	return semget (key, 1, sem_flags);
}
/*Desasignamos el semáforo. Todos los usuarion tuvieron que haber finalizado con él 
Retorna -1 si falla*/

int binary_semaphore_deallocate (int semid){
	union semun ignored_argument;
	return semctl (semid, 1, IPC_RMID, ignored_argument);
}

/*Inicializamos un semáforo binario con el valor 1*/
int binary_semaphore_initialize (int semid){
	union semun argument;
	unsigned short values[1];
	values[0] = 1;
	argument.array = values;
	return semctl (semid, 0, SETALL, argument);
}


/*Esperamos en el semáforo.*/
int binary_semaphore_wait (int semid){
	struct sembuf operations[1];
/* Usamos el semáforo*/
	operations[0].sem_num = 0;
/* Decrementamos en 1. */
	operations[0].sem_op = -1;
	operations[0].sem_flg = SEM_UNDO;
	return semop (semid, operations, 1);
}

int binary_semaphore_post (int semid){
	struct sembuf operations[1];
/* Usamos el semaforo*/
	operations[0].sem_num = 0;
/* Incrementamoes en 1. */
	operations[0].sem_op = 1;
	operations[0].sem_flg = SEM_UNDO;
	return semop (semid, operations, 1);
}

int main(){
	key_t key;
	int k = binary_semaphore_allocation(key, 0);
	printf("El id del semáforo es: %d\n", k);
	printf("Inicializamos el semáforo\n");
	binary_semaphore_initialize(k);
	binary_semaphore_deallocate(k);
	return 0;	
}
