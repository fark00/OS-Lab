#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define THREADS 4
#define SIZE 5
#define THREADS 3

sem_t sem1;
int product = 0;
int A[5] = {1, 2, 3, 4, 5};
int B[5] = {5, 4, 3, 2, 1};
void *routine(void * id )
{
	int idx=(int)id;
	sem_wait(&sem1);
	//beginning of critical section
	for(int i = id; i < SIZE; i += THREADS)
	{
		product += A[idx] * B[idx];
        	printf("thread=%d and product=%d \n",idx,product);
	}
	sleep(1);
	//end of critical section
	sem_post(&sem1);
	pthread_exit((void *)idx);
}

int main ()
{
	sem_init(&sem1,0,1);
	pthread_t threads[THREADS];
	for ( int i=0;i<THREADS;i++)
		pthread_create(&threads[i],NULL,routine,(void *)i);
	for (int i=0; i<THREADS; i++)
		pthread_join(threads[i],NULL);
return 0;
}
