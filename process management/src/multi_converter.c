#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <converters.h>

#define _XOPEN_SOURCE 700

int curr[5];

int main(int argc, char * argv[])
{
	int n = 5;
	if (argc > 1){
		char * src_currency = argv[1];
		double src_amount = atoi(argv[2]);

		int j;

		for (j = 0; j<n ; j++)
		{
			curr[j] = j;
		}

		pid_t pids[n];
		int i;
	
		for (i=0; i<n; i++)
		{
			if ((pids[i] = fork()) < 0)
			{
				perror("fork() error"); exit(1);
			}
			else if ((pids[i] == 0))
			{
				int ou_curr;
				char * output_curr;
				double amt;
				
				ou_curr = curr[i];
				output_curr = determine_currency(ou_curr);
				amt = convert(src_currency, output_curr, src_amount);
				display_result(ou_curr, amt);
				exit(0);
				
			}
		}
		int status;
		pid_t pid;
		while (n > 0)
		{
			pid = wait(&status);
			--n;
		}
		
		
	}
	else
	{
		printf("No arguments passed\n");
		exit(1);
	}
	return 0;


}
