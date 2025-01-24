#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int factorial(void* param);

int main(char argc, char* argv[]) {
    pthread_t* thread_handle;
    long thread_count = 10;
    int args = 10;
    
    thread_handle = malloc(thread_count*sizeof(pthread_t));
    
    for (int t = 0; t < thread_count; t++) {
        pthread_create(&thread_handle[t], NULL, factorial, (void*)args);
    }
    
    for (int t = 0; t < thread_count; t++) {
        pthread_join(&thread_handle[t], NULL);
    }
    
    return 0;
}

int factorial(void* param) {
    long n = (long) param;
    
    if (n <= 1) 
        return 1;
    else 
        return n * factorial((void*)(n - 1));
}