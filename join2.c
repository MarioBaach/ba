#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3

void *BusyWork(void *null)
{
  int i;
  int result;
  for (i=0; i<1000000; i++)
    {
      result = ( (int) 100 * ((double) rand() / ((double)(RAND_MAX)+(double)(1)) ) ); 
    }
  printf("Thread %d: result = %d\n", (int) pthread_self(), result);
  pthread_exit((void *) 0);
}

int main(int argc, char *argv[])
{
  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  int rc, t, status;

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(t=0;t<NUM_THREADS;t++)
    {
      rc = pthread_create(&thread[t], &attr, BusyWork, NULL); 
      if (rc)
	{
	  printf("ERROR; return code from pthread_create() is %d\n", rc);
	  exit(EXIT_FAILURE);
	}
      printf("Main %d: Creating thread %d\n", (int) pthread_self(), (int) thread[t] );
    }

  /* Free attribute and wait for the other threads */
  pthread_attr_destroy(&attr);
  for(t=0;t<NUM_THREADS;t++)
    {
      rc = pthread_join(thread[t], (void **)&status);
      if (rc)
	{
	  printf("ERROR return code from pthread_join() is %d\n", rc);
	  exit(EXIT_FAILURE);
	}
      printf("Main: Completed join with thread %d status= %d\n", (int) thread[t], status);
    }

  pthread_exit(NULL);
}

