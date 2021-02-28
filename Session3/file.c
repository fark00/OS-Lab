
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	if(strcmp(argv[1], "-c") == 0)
	{
		int a = open(argv[3], O_CREAT | O_RDWR, strtol(argv[2], NULL, 8));
		close(a);
	}
	if(strcmp(argv[1], "-w") == 0)
	{
		int a = open(argv[2], O_CREAT | O_WRONLY, 00755);
		char str[200];
		fgets(str, 200, stdin);
		write(a, str, strlen(str));
		close(a);
	}
	if(strcmp(argv[1], "-r") == 0)
	{
		int a = open(argv[2], O_RDONLY, 00777);
		char str[200];
		read(a, str, 199 );
		fprintf(stdout,"%s", str);
		close(a);

	}
	if(strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "-make") == 0)
	{
		int s_num = atoi(argv[5]);
		int e_num = atoi(argv[6]);
		for(int i = s_num; i <= e_num; i++)
		{
			char str[200];
			sprintf(str,"%s/%s%i.%s",argv[2],argv[3],i,argv[4]);
			int a = open(str,O_CREAT,00777);
			close(a);
		}
	}
	return 0;
}
