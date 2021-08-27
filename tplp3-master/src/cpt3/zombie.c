#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main (){
	pid_t child_pid;
/* Creamos un proceso hijo. */
	child_pid = fork ();
	if (child_pid > 0) {
/* Este es el proceso padre, esperamos un minuto. */
		sleep (10);
	}else {
	/* Este es el proceso hijo, salimos. */
		exit (0);
	}
	return 0;
}
