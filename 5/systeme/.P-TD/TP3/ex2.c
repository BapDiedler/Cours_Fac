#include <pthread.h>
#include <stdio.h>

void *thread_func(void *);

int main(int argc, char const *argv[])
{
    pthread_t thread1[10];
    for (size_t i = 0; i < 10; i++)
    {
        pthread_create(thread1 + i * sizeof(pthread_t), NULL, thread_func, &i);
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(thread1[i * sizeof(pthread_t)], NULL);
    }
    return 0;
}

void *thread_func(void *args)
{
    int *i = (int *)args;
    printf("Bonjour - %d\n", *i);
}