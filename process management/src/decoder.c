/**** decoder.c ****/

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


#define _XOPEN_SOURCE 700


int magicsq[3][3] = {{4, -1, 8}, {-1, -1, -1}, {2, -1, 6}};


int check() {
	int i, j, sums[8];
	for (i = 0; i < 8; i++) 
		sums[i] = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sums[i] += magicsq[i][j];
			sums[i+3] += magicsq[j][i];
			if (i == j) sums[6] += magicsq[i][j];
			if ((i+j) == 2) sums[7] += magicsq[i][j];
		}
	}
	int result = 1;
	i = 1;
	while ((i < 8) && (result == 1)) {
		if (sums[0] != sums[i])
			result = 0;
		i++;
	}
	return result;
}


void display() {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			printf("  %d", magicsq[i][j]);
		printf("\n");
	}
	printf("\n");
}


int solve(int x) {
	/* CODE THAT EVERY CHILD PROCESS EXECUTES */
	int i = 0;
	int sing_sum = 0;
	magicsq[0][1] = x;

	for (i=0; i<3; i++)
	{
		sing_sum += magicsq[0][i];
	}
	int b, c, d, e;
	int b_sum = 0, c_sum = 0, d_sum = 0, e_sum =0; 
	
	for(i=0; i<3; i++) 
	{
		b_sum += magicsq[i][0];
		d_sum += magicsq[i][2];
		e_sum += magicsq[2][i];
	}
	b = sing_sum - (b_sum + 1);
	d = sing_sum - (d_sum + 1);
	c = sing_sum - (b + d);
	e = sing_sum - (e_sum + 1);
	
	magicsq[1][0] = b, magicsq[1][1] = c, magicsq[1][2] = d, magicsq[2][1] = e;
	
	if (check())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main(int argc, char **argv)
{	
	/* PARENT PROCESS */
	pid_t pids[10];
	int i;
	int val;
	int n = 10;
	
	printf("%s\n",argv[0]);

	for (i = 0; i < n; i++)
	{
		if ((pids[i] = fork()) < 0)
		{
			perror("fork() error"); exit(1);
		}
		else if (pids[i] == 0)
		{
			val = solve(i);
			if (val == 0) 
			{	
				printf("%d\n",i);
				display();
				exit(0);
			}
			else
			{
				exit(1);
			}
			
		}
	}

	int status;
	pid_t pid;
	while (n > 0)
	{
		pid = wait(&status);
		printf("Child pid = %d exited as 0x%x. \n", pid, status);
		--n;
	}
	return 0;	

}
