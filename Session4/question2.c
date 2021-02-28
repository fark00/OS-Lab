#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXCHILD 5
int main(){
	pid_t child [MAXCHILD];
	int inChild=0;
	int status=0;
	for (int i=0;i<MAXCHILD;i++)
	{
		child[i]=fork();
		if(child[i]==0)
		{
			inChild=1;
			break;
		}
	}
	while (inChild==1)
	{
		srand(getpid());
		int r = rand()%1000;
		sleep(r);
		printf("Message from child %d, waited for %d seconds.\n",getpid(),r);
		inChild=-1;
	}
	while(inChild==0)
	{
		int c1 = 0;
		while(1)
		{
			int status = 0;
			for(int i = 0; i < MAXCHILD; i++)
			{
				int child_s = waitpid(child[i], &status, WNOHANG);
				if( child_s != 0)
				{
					child[i] = fork();
					if(child[i] == 0)
					{
						srand(child[i]);
						int random = rand()%1000;
						sleep(random);
						printf("Message from child %d, waited for %d seconds.\n", getpid(), random);
						c1 = 1;
						break;
					}
				}
			}
			if(c1 == 1)
				break;
			sleep(5);
		}
		if(c1 == 1)
			break;
	}
	return 0;
}
