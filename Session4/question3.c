#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h> //gettimeofday
#include <time.h> //time
#include<fcntl.h>
#include<sys/wait.h>

int main(int argc,char ** argv)
{
	struct timeval start,stop;
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	gettimeofday(&start,NULL);
        int result = fork();
	if(result == 0)
	{
		execlp(argv[1], argv[1], NULL);
	}
	if(result != 0)
	{
		wait(NULL);
		gettimeofday(&stop,NULL);
        	long sec=stop.tv_sec-start.tv_sec;
        	float m1=start.tv_usec;
        	float m2=stop.tv_usec;
        	long elapsed = sec*1000+(m2-m1)/1000;
		int _file = open("log.txt",O_CREAT|O_APPEND|O_RDWR,00777);
		char str[200];
		sprintf(str,"%d-%02d-%02d\t%02d:%02d\t%ld/%s\n",timeinfo->tm_year+1900,timeinfo->tm_mon,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,elapsed,argv[1]);
		write(_file,str,strlen(str));
		close(_file);
	}
	return 0;
}
