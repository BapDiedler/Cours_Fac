#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define SIZE 1000
#define N 50
#define NB_THREAD 10

int tab[SIZE];

void *thread_func(void *args);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        tab[i] = rand() % 100;
    }

    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * NB_THREAD);
    for (int i = 0; i < NB_THREAD; i++)
    {
        pthread_create(&(threads[i]), NULL, thread_func, (void *)&i);
    }

    for (int i = 0; i < NB_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    return 0;
}

void recherche_simple(int th);

void *thread_func(void *args)
{
    int *i = (int *)args;
    recherche_simple(*i);
    return NULL;
}

void recherche_simple(int th)
{
    for (int i = th; i < SIZE; i += NB_THREAD)
    {
        if (tab[i] == N)
        {
            printf("%d - (%d, %d )\n", th, i, tab[i]);
        }
        usleep(10000);
    }
}
