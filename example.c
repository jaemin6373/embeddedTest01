#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define MUTEX_ENABLE   1000
pthread_t tr_id[2];
int jobIndex = 0; //순차적으로 증가

pthread_mutex_t lock;
pthread_mutex_t twoLock;

void* do_SomeThing(void *arg)
{
#if MUTEX_ENABLE							//mutex을 사용했을 경우 
	pthread_mutex_lock(&lock);	//lock으로 다른 스레드의 동시 수행 차단
#endif
	unsigned long	i = 0;
	jobIndex += 1;
	printf("\n Job %d started\n", jobIndex);
	
	for(i=0; i<(0xFFFFF);i++); // delay
	printf("\n Job %d finished\n", jobIndex);
	
#if MUTEX_ENABLE
	pthread_mutex_unlock(&lock);	// 다른 스레드가 수행할수 있도록 lock 해제 
#endif
	return NULL;
}
//두 스레드에서 수행할 함수. 할당 받은 job을 특정 delay 후 끝냄

int main(void)
{
  int i=0;
  int err;

  if (pthread_mutex_init(&lock, NULL) != 0)
  {
    printf ("\n Mutex Init Failed!!\n");
    return 1;
  }

   while (i<2)
   {
      err = pthread_create(&(tr_id[i]), NULL, &doSomething, NULL);
      if (err != 0)
          printf ("Thread Create Error: [%d]\n", err);
      i++;
   }
   pthread_join (tr_id[0], NULL);
   pthread_join (tr_id[1], NULL);
   return 0;
}

