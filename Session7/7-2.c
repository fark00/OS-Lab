#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#define MAXCHILD 5
#define MAXIMUM 100
int total = 0;
char path[20];
char buffer[255];
int pid[MAXCHILD];

void handler1(int signo)
{
	int value = 0;
	int pipe;
	pipe = open(path, O_RDWR);
	switch(signo)
	{
		case SIGUSR1:
			read(pipe, buffer, 255);
			for(int i = 0; i < strlen(buffer); i++)
			{
				total += buffer[i] - '0';
				printf("Total is: %d\n", total);
				if(total > MAXIMUM){
                    for(int i=0; i<MAXCHILD;i++)
						kill(pid[i], SIGKILL);
					exit(0);
			   }
			}
			bzero(buffer, 255);
			break;
	}
}
int main(){
	int inChild=0;
	int pipe;
	sprintf(path,"sig1.pipe");
	mkfifo(path,0777);
	struct sigaction action1;
	action1.sa_handler = handler1;
	action1.sa_flags 
	sigaction(SIGUSR1, (struct sigaction *) &action1
	for(int i=0 ; i<MAXCHILD ; i++){
		pid[i]=fork();
		if(pid[i]==0){
			inChild=1;
			break;
		}
	}
	if(inChild==1){
		pipe=open(path,O_RDWR);
		while(1){	
			srand(time(0));
			int r = rand()%10;
			sleep(r);
			sprintf(buffer, "%d", r);
			write(pipe, buffer, strlen(buffer));
			pid_t parent= getppid();
			kill(parent, SIGUSR1);
			printf("child %d writes in pipe %d\n", getpid(), r);
		}
	}
	if(inChild==0)
		while(1);				
	
}


