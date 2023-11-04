#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define NB_THREAD 10

int lecteur_count = 0;

static pthread_mutex_t lecture_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t base_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t ecriture_lock = PTHREAD_MUTEX_INITIALIZER;

void *run(void *);

int main(int argc, char const *argv[])
{
	int id[NB_THREAD];// tableau d'identifiant pour voir s'il y a des risques de famine.
    for(int i=0; i<NB_THREAD; i++){
        id[i] = i;
    }

    srand(time(NULL));
    pthread_t thread1[NB_THREAD];
    for (size_t i = 0; i < NB_THREAD; i++)
    {
        pthread_create(thread1 + i * sizeof(pthread_t), NULL, run, (void*)&id[i]);
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
	int* id = (int*)args;
    while (1)
    {
        if ((rand() % 2) == 0)
        {
            lire(*id);
        }
        else
        {
            ecrire(*id);
        }
    }
}

void lire(int id)
{
    pthread_mutex_lock(&ecriture_lock);
    pthread_mutex_lock(&lecture_lock);
    {
        if (lecteur_count == 0)
        {
            pthread_mutex_lock(&base_lock);
        }
        lecteur_count++;
    }
    pthread_mutex_unlock(&lecture_lock);
    pthread_mutex_unlock(&ecriture_lock);

    printf("lire debut %d\n",id);
    usleep(rand() % 500000);
    printf("lire fin\n");

    pthread_mutex_lock(&lecture_lock);
    {
        lecteur_count--;
        if (lecteur_count == 0)
        {
            pthread_mutex_unlock(&base_lock);
        }
    }
    pthread_mutex_unlock(&lecture_lock);
}

void ecrire(int id)
{
    pthread_mutex_lock(&ecriture_lock);
    pthread_mutex_lock(&base_lock);
    pthread_mutex_unlock(&ecriture_lock);

    printf("ecrire debut %d\n",id);
    usleep(rand() % 500000);
    printf("ecrire fin\n");

    pthread_mutex_unlock(&base_lock);
}
