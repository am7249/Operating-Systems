#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 5

int cont = 0;

void sig_hand(int sig){
	//printf("sig: %d\n",sig);
	
	if (sig == SIGUSR1){
		printf("SIGUSR1 received at %d\n",getpid());
	}
	else if (sig == SIGUSR2){
		printf("SIGUSR2 received at %d\n", getpid());
	}
	else if (sig == SIGINT){
		printf("SIGINT received at %d\n", getpid());
	}

}


int main(int argc, char ** argv){

	sigset_t sig_proc; int i; struct sigaction action; pid_t LD; pid_t PP;
	sigemptyset(&sig_proc);
	
	action.sa_mask = sig_proc;
	action.sa_flags = 0;
	action.sa_handler = sig_hand;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	sigaction(SIGINT, &action, 0);
	PP = getpid();

	printf("PP: %d\n", PP);

	pid_t pid_current, pid_parent, pid_child;
	pid_current = getpid();
	for (i=0; ((i<N)&&((pid_child =fork()) == 0)); i++){
		printf("process created. pid: %d\n", getpid());
		printf("i: %d\n",i);
		printf("parent pid: %d\n\n", getppid());
		pid_parent = pid_current;
		pid_current = getpid();
	
	}
	if (i==N){
		LD = getpid();
		//printf("LD: %d\n",LD);
		printf("Start first wave of SIGUSR1 \n");
		kill(pid_parent, SIGUSR1);

		pause();
		printf("End of second wave \n");
		printf("wait 5 seconds before third wave \n");
		sleep(5);

		printf("Start third wave of SIGINT \n");
		kill(pid_parent, SIGINT);
	}

	else if ((i>0) && (i<N)){
		
		pause();
		
		kill(pid_parent, SIGUSR1);
		
		pause();

		kill(pid_child, SIGUSR2);

		pause();

		kill(pid_parent, SIGINT);
	}
	
	else if (i==0){
		pause();
		printf("End of first wave of SIGUSR1 \n");
		printf("Wait 5 seconds before second wave \n");
		sleep(5);

		printf("Start of second wave of SIGUSR2 \n");
		kill(pid_child, SIGUSR2);

		pause();

		printf("End of program \n"); 
	}	

	//wait(NULL);
	
	return EXIT_SUCCESS;

}
