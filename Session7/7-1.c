#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#define MAX_TRY 5
int count = 0;
void handler1(int signo)
{
	switch(signo)
	{
		case SIGINT:
		printf("Interrupt Signal received \n");
		count++;
		if(count > MAX_TRY)
		{
			exit(0);
		}
		break;
	}
}
int main()
{
	struct sigaction action1;
	action1.sa_handler = handler1;
	action1.sa_flags = 0;
	sigaction(SIGINT,(struct sigaction *) &action1,NULL);
	while(1);
	return 0;
}
