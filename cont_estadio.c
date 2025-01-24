#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

long long publico = 0;

void* contar_publico(void *param);

int main(int argc, char* argv[]) {
    pthread_t t1, t2, t3, t4;
    long n = 5000000;
    
    pthread_create(&t1, NULL, contar_publico, (void*) n);
    pthread_create(&t2, NULL, contar_publico, (void*) n);
    pthread_create(&t3, NULL, contar_publico, (void*) n);
    pthread_create(&t4, NULL, contar_publico, (void*) n);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    
    printf("Pessoas contadas: %lld\n", publico);
    
    return 0;
}

void* contar_publico(void *param) {
    long n = (long) param;
    
    for (int i = 0; i < n; i++) {
        publico++;
        if (i % 1000 == 0) {
            printf("%lld\n", publico);
        }
    }
    
    return NULL;
}