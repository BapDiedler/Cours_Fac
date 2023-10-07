#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define NB_THREAD 10

static pthread_mutex_t mutex_stock = PTHREAD_MUTEX_INITIALIZER;

/**
 * 5.1
 * 
 * respecté     : C1
 * non respecté : C2, C3
 * 
 * 5.2
 * 
 * respecté     : C2, C3
 * non respecté : C1
 */

void *run(void *);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    pthread_t thread1[NB_THREAD];
    for (size_t i = 0; i < NB_THREAD; i++)
    {
        pthread_create(thread1 + i * sizeof(pthread_t), NULL, run, &i);
    }

    for (size_t i = 0; i < NB_THREAD; i++)
    {
        pthread_join(thread1[i * sizeof(pthread_t)], NULL);
    }
    return 0;
}

void lire();
void ecrire();

void *run(void *args)
{
    while (1)
    {
        if ((rand() % 2) == 0)
        {
            lire();
        }
        else
        {
            ecrire();
        }
    }
}

void lire()
{
    pthread_mutex_lock(&mutex_stock);
    printf("lire debut\n");
    usleep(rand() % 500000);
    printf("lire fin\n");
    pthread_mutex_unlock(&mutex_stock);
}

void ecrire()
{
    pthread_mutex_lock(&mutex_stock);
    printf("ecrire debut \n");
    usleep(rand() % 500000);
    printf("ecrire fin\n");
    pthread_mutex_unlock(&mutex_stock);
}