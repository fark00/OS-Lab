#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAXCHILD 5
int main(){
	int pid[MAXCHILD];
	int  child_id = -1;
	int inChild=0;
	int pipe;
	char path[20];
	char buffer[255];
	int value;
	sprintf(path,"1.pipe");
	mkfifo(path,0777);
	for(int i=0 ; i<MAXCHILD ; i++){
		pid[i]=fork();
		if(pid[i]==0){
			inChild=1;
			child_id=i;
			break;
		}
	}
	if(inChild==1){
		printf("child %d starts\n", child_id);
		pipe=open(path,O_RDWR);
		while(1){
			read(pipe,buffer,255);
			value=atoi(buffer);
			printf("child %d pipevalue: %d\n", child_id, value);
			if(value>0 && value==child_id){
				sprintf(buffer,"%d", value-1);
				write(pipe,buffer,strlen(buffer));
			}
			else if(value==0){
				write(pipe,buffer,strlen(buffer));
				printf("child %d reach the point\n", child_id);
				exit(0);
			}
			else{
				write(pipe,buffer,strlen(buffer));
			}
			sleep(1);
		}
	}
	if(inChild==0){
		pipe=open(path,O_WRONLY);
		sprintf(buffer,"%d", MAXCHILD-1);
		write(pipe,buffer,strlen(buffer));
		for(int i=0; i<MAXCHILD;i++)
			waitpid(pid[i],0,0);
		printf("The program finished successfully\n");
		return 0;
	}
}

