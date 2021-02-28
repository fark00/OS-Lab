#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int clause = 1;
	while(clause)
	{
		pid_t pid = fork();
		if(pid == 0)
		{
			printf("hi, i am child with pid: %d\n", getpid());
			clause = 0;
		}
		if(pid != 0)
		{
			sleep(2);
		}
	}
	return 0;
}
