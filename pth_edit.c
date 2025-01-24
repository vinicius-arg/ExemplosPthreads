#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>

void *Hello(void* param);  /* Thread function */
void *Hello2(void* param); /* My hello function */

/*--------------------------------------------------------------------*/
long t1_param = 1;
   
int main(int argc, char* argv[]) {
   long t2_param = 10;
   
   pthread_t t1;
   pthread_t t2;
   
   pthread_create(&t1, NULL, Hello, (void*) t1_param);  
   pthread_create(&t2, NULL, Hello2, (void*) t2_param);
   
   t1_param = 2;
   
   for (int i = 0; i < 5; i++) {
     // printf("Hello da thread principal!\n");
      sleep(1);
   }
   
   pthread_join(t1, NULL);
   pthread_join(t2, NULL);

   return 0;
}  /* main */

/*-------------------------------------------------------------------*/
void *Hello(void* param) {
   long my_id = (long) param;  /* Use long in case of 64-bit system */ 

   for (int i = 0; i < 5; i++) {
      printf("%ld\n", sizeof(int));
      printf("Hello da thread 'Hello' => %ld\n", my_id);
      usleep(500000);
   }
   
   return NULL;
}  /* Hello */

void *Hello2(void* param) {
   long times = (long) param;
   
   for (int i = 1; i <= times; i++) {
      //printf("Hello da thread 'Hello2' => %d\n", i);
      sleep(1);
   }
   
   return NULL;
}
