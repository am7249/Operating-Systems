#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void calc1(){
	int i;
	for(i=0; i<1E8; i++);
	//printf("first i: %d\n", i);
}

void calc2(){
	int i;
	for(i=0; i<1E8; i++);
	//printf("second i: %d\n",i);
}

void barrier(int i, pid_t pid_child[2], pid_t pid_parent){
	sigset_t sig_set;
	sigemptyset(&sig_set);
	sigaddset(&sig_set,SIGUSR1); 
	sigaddset(&sig_set,SIGUSR2); 
	sigprocmask(SIG_SETMASK, &sig_set, NULL);	
	
	printf("calc1 starts for %d\n",i);
	calc1();
	printf("calc1 ends for %d\n",i);
	//printf("==========\n");


	if (i==2){
		kill(pid_child[0], SIGUSR1);
		kill(pid_child[1], SIGUSR1);
	}
	else if (i==1){
		kill(pid_child[0], SIGUSR2);
		kill(pid_parent, SIGUSR1);
	}
	else if (i==0){
		kill(pid_child[1], SIGUSR1);
		kill(pid_parent, SIGUSR2);
	}
	int move;
	while(move != 2){
		move = 0;
		sigpending(&sig_set);
		if(sigismember(&sig_set, SIGUSR2)){
			move++;
		}

		if(sigismember(&sig_set, SIGUSR1)){
			move++;
		}
		//printf("this is i: %d\n",i);
	}
}


int main(int argc, char * argv[]){

	int i=0;
	//int move = 0;
	pid_t pid_child [2];
	pid_t pid_parent;
	pid_parent = getpid();

	
	while ((i<2) && ((pid_child [i] = fork()) != 0)){
		i++;
	}
	//printf("==========\n");
	
	barrier(i, pid_child, pid_parent);
	
	printf("calc2 resumes for process: %d\n",i);
	calc2();
	printf("End Process %d\n",i);
	return EXIT_SUCCESS;

}
