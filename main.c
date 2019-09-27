#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
 
pthread_t thread_object_1;
pthread_t thread_object_2;

pthread_mutex_t	lockInput;

char buffer[1000];
int ready=0;

void *threadFunc1(void *arg)
{
	printf ("Thread Func1 Args: %d\r\n",*(int *)(arg));
	while (1)
	{
		pthread_mutex_lock(&lockInput);
		if (ready == 0)
		{
			printf ("Thread 1: $ ");
			gets(buffer);
			ready = 1;
			pthread_mutex_unlock (&lockInput);
		}
		else
		{
			pthread_mutex_unlock (&lockInput);
			usleep(100);
		}
	}
}

void *threadFunc2(void *arg)
{
	printf ("Thread Func2 Args: %d\r\n",*(int *)(arg));
	while (1)
	{
		pthread_mutex_lock(&lockInput);
		if (ready == 1)
		{
			printf ("->Thread 2: Output [%s]\r\n",buffer);
			ready = 0;
			pthread_mutex_unlock (&lockInput);
		}
		else
		{
			pthread_mutex_unlock (&lockInput);
			usleep(100);
		}
	}
}
int main(void)
{
	int a=8282;
	int b=2828;

	pthread_mutex_init(&lockInput, NULL);

	pthread_create(&thread_object_1, NULL, threadFunc1, &a);
	pthread_create(&thread_object_2, NULL, threadFunc2, &b);

	pthread_detach(thread_object_1);
	pthread_detach(thread_object_2);

	while(1)
	{
		sleep(10000);
	}
}
