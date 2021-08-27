#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
/*Tenemos que definir la union senum nosotros mismos*/
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

int binary_semaphore_allocation (key_t key, int sem_flags){
	return semget (key, 1, sem_flags);
}

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

int main(){
	key_t key = 10;
	int k = binary_semaphore_allocation(key, 1);
	binary_semaphore_initialize(k);
	printf("Se inicializó el semáforo\n");
	binary_semaphore_deallocate(k);
	
	return 0;
} 
