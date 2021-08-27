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

int main(){
	key_t key;
	int k = binary_semaphore_allocation(key, 1);
	printf("El id del semáforo es: %d\n", k);
	binary_semaphore_deallocate(k);
	return 0;
}
