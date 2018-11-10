#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 4

int i, j;

int main(int argc, char * argv[]){

	sigset_t sig_set;
	sigemptyset(&sig_set);
	sigaddset(&sig_set,10); 
	sigaddset(&sig_set,11); 
	sigaddset(&sig_set,12);
	sigaddset(&sig_set,13);
	sigprocmask(SIG_SETMASK, &sig_set, NULL);

	pid_t pid;
	j = 0;
	for(i=0; ((i<N) && ((pid=fork()) != 0)); i++){
		printf("i: %d, j: %d \n",i,j);
	}

	if ((i%2 == 1) && (pid == 0)){
		while ((j<i) && ((pid = fork())==0)){
			j++;
			printf("i: %d, j: %d \n",i,j);
		}
	}
	//signal for the parent process
	if(i==N){
		int sig_rec = 0;
		while(sig_rec != N){
			sig_rec = 0;
			sigpending(&sig_set);
			int k;
			for(k=0; k<N; k++){
				if(sigismember(&sig_set, k+10)){
					sig_rec++;
				}
			}
				
		}
		printf("killed the parent process | i, j = %d %d\n",i,j);
	}
	//signal for the decsendant processes
	else{
		//signal for processes with no children
		if((i==j)||((i%2)==0)){
			
			kill(getppid(),i+10);
			printf("killed leaf processes | i, j = %d %d\n",i,j);
		}
		//signal for processes with one children
		else{
			int sig_rec = 0;
			while(sig_rec != 1){
				sigpending(&sig_set);
				if(sigismember(&sig_set, i+10)){
					sig_rec++;
				}
			}	
			kill(getppid(),i+10);
			printf("killed processes with 1 child | i, j = %d %d\n",i,j);
		}
	}

	return 0;

}
