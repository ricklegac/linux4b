#include<signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

sig_atomic_t child_exit_status;
void clean_up_child_process (int signal_number){
/* Clean up the child process. */
	int status;
	wait (&status);
/* Store its exit status in a global variable.*/
	child_exit_status = status;
}

int main (){
/* Handle SIGCHLD by calling clean_up_child_process. */
	struct sigaction sigchld_action;
	memset (&sigchld_action, 0, sizeof (sigchld_action));
	sigchld_action.sa_handler = &clean_up_child_process;
	sigaction (SIGCHLD, &sigchld_action, NULL);
	pid_t child_pid;
	child_pid = fork ();
	if (child_pid > 0) {
		printf("Soy el proceso padre\n");
		sleep(10);	
	}else {	
		printf("Soy el proceso hijo\n");
	}
	return 0;
}
