#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

long long publico = 0;

pthread_mutex_t mutex; // Por padrão destravado

void* contar_publico(void *param);
void inc_publico();

int main(int argc, char* argv[]) {
    pthread_t t1, t2, t3, t4;
    long n = 2000000;
    
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
        inc_publico(); // Região crítica, concorrência em escrita
        
        // if (i % 1000 == 0) printf("%lld\n", publico);
    }
    
    return NULL;
}

void inc_publico() {
    /* 
     Suspende a execução de outras threads enquanto estiver processando, apenas
     uma thread pode travar o mutex ao mesmo tempo.
    */
    pthread_mutex_lock(&mutex); 
    publico++;
    pthread_mutex_unlock(&mutex); 
    // Destrava após processar, liberando acesso para outras threads.
}