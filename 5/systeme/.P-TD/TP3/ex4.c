#include <pthread.h>
#include <stdio.h>

volatile int var;

static pthread_mutex_t mutex_stock = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *);

int main(int argc, char const *argv[])
{
    var = 0;
    pthread_t thread1[10];
    for (size_t i = 0; i < 10; i++)
    {
        pthread_create(thread1 + i * sizeof(pthread_t), NULL, thread_func, &i);
    }

    for (size_t i = 0; i < 10; i++)
    {
        pthread_join(thread1[i * sizeof(pthread_t)], NULL);
    }
    printf("\t%d\n", var);
    return 0;
}

void *thread_func(void *args)
{
    for (size_t i = 0; i < 10000; i++)
    {
        pthread_mutex_lock(&mutex_stock);
        var++;
        pthread_mutex_unlock(&mutex_stock);
    }
    printf("%d\n", var);
}