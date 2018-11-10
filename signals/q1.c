#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


#define N 5

void sig_hand(int sig){

	//printf("\nreceived signal: %d\n",sig);
	alarm(N);

}

unsigned int mysleep(int sec){

	sigset_t sig_proc;
	struct sigaction action;
	
	sigemptyset(&sig_proc);
	
	action.sa_mask = sig_proc;
	action.sa_flags= 0;
	action.sa_handler = sig_hand;
	sigaction(SIGALRM, &action, 0);


	alarm(sec);
	pause();



}


int main(int argc, char ** argv){

	int i;
	/* for loop to test different sleep times */
	for (i=0; i< N; i++){	
		printf("begin cycle. waiting time: %d \n", i+1);
		mysleep(i+1);
		printf("end program. \n");
	}
	return EXIT_SUCCESS;
}
