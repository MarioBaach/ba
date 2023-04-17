#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Parameters to print_function.  */

struct char_print_parms
{
  char character;  /* The character to print.  */
  int count;       /* The number of times to print it.  */
};

/* Prints a number of characters to stdout, as given by PARAMETERS,
   which is a pointer to a struct char_print_parms.  */

void* char_print (void* parameters)
{
  /* Cast the cookie pointer to the right type.  */
  struct char_print_parms* p = (struct char_print_parms*) parameters;
  int i;

  for (i = 0; i < p->count; ++i)
    fputc (p->character, stdout);
  return NULL;
}

/* The main program.  */

int main ()
{
  pthread_t thread1_id;
  pthread_t thread2_id;
  struct char_print_parms thread1_args;
  struct char_print_parms thread2_args;
  int rc;

  /* Create a new thread to print 30000 x's.  */
  thread1_args.character = 'x';
  thread1_args.count = 30000;
  rc = pthread_create (&thread1_id, NULL, &char_print, &thread1_args);
  if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(EXIT_FAILURE);
    };

  /* Create a new thread to print 20000 o's.  */
  thread2_args.character = 'o';
  thread2_args.count = 20000;
  rc = pthread_create (&thread2_id, NULL, &char_print, &thread2_args);
  if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(EXIT_FAILURE);
    };
 
  /* Make sure the first thread has finished.  */
  pthread_join (thread1_id, NULL);
  /* Make sure the second thread has finished.  */
  pthread_join (thread2_id, NULL);
  /* Now we can safely return.  */

  printf("\nMain: The first thread and the second thread have finished.\n");
  return EXIT_SUCCESS;
}
