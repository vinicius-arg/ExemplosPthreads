/* File:  
 *    pth_hello.c
 *
 * Purpose:
 *    Illustrate basic use of pthreads:  create some threads,
 *    each of which prints a message.
 *
 * Input:
 *    none
 * Output:
 *    message from each thread
 *
 * Compile:  gcc -g -Wall -o pth_hello pth_hello.c -lpthread
 * Usage:    ./pth_hello <thread_count>
 *
 * IPP:   Section 4.2 (p. 153 and ff.)
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>

/* Global variable:  accessible to all threads */
int thread_count;  

void *Hello(void* rank);  /* Thread function */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;  /* Use long in case of a 64-bit system */
   pthread_t* thread_handles; 
   
   thread_count = 40; 

   thread_handles = malloc (thread_count*sizeof(pthread_t)); 

   for (thread = 0; thread < thread_count; thread++)  
      pthread_create(&thread_handles[thread], NULL, Hello, (void*) thread);  
   
   
   printf("Hello from the main thread\n");
   
   //sleep(10);
   for (thread = 0; thread < thread_count; thread++){ 
      pthread_join(thread_handles[thread], NULL); // Bloqueante
      printf("Thread %ld joined!\n", thread);
   }
   
   free(thread_handles);
   printf("Main thread exit\n");
   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* rank) {
   long my_rank = (long) rank;  /* Use long in case of 64-bit system */ 
   printf("Hello from thread %ld of %d\n", my_rank, thread_count);
   //sleep(10);
   printf("Thread %ld of %d exit!\n", my_rank, thread_count);
   return NULL;
}  /* Hello */

