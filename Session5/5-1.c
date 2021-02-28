#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    enum { NUM_CHILDREN = 5, MAXIMUM = 50 };
    int fd[NUM_CHILDREN][2];
    pid_t pid[NUM_CHILDREN];
    int inchild = 0;
    int total = 0;
    int id = 0;
    char buffer[256];
    for (id = 0; id < NUM_CHILDREN; id++)
    {
        pipe(fd[id]);
        pid[id] = fork();
        if (pid[id] < 0)
		printf("ERROR!");
        if (pid[id] == 0)
        {
			inchild = 1;
            for (int j = 0; j < id; j++)
            {
                close(fd[j][0]);
                close(fd[j][1]);
            }
            close(fd[id][0]);   // Close read end of pipe
			break;
        }
    }
    while (inchild == 1)
    {
	    srand(getpid());
	    int random = rand()%10;
	    sprintf(buffer,"%d",random);
	    write(fd[id][1], buffer, 255);
	    sleep(2);
    }
    while (inchild == 0)
    {
	    for(int i = 0; i < NUM_CHILDREN; i++)
	    {
		    if(read(fd[i][0], buffer, 255) > 0)
		    {
			    int num = atoi(buffer);
			    total += num;
			    printf("Total is: %d\n", total);
			    if(total >= MAXIMUM)
			    {
				for(int k = 0; k < NUM_CHILDREN; k++)
					kill(pid[k], SIGKILL);
				exit(0);
			    }
		    }
	    }
    }
    return 0;
}
