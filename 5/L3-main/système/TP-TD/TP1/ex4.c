#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define SIZE 1000

void recherche_simple(int tab[], int d, int n, int size);
void recherche_parallele(int tab[], int n, int size);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int tab[1000];
    for (size_t i = 0; i < 1000; i++)
    {
        tab[i] = rand() % 100;
    }

    time_t begin = time(NULL);
    recherche_simple(tab, 0, 0, SIZE);
    time_t end = time(NULL);
    printf("\n%ds\n", (end - begin));

    begin = time(NULL);
    recherche_parallele(tab, 0, SIZE);
    end = time(NULL);
    printf("\n%ds\n", (end - begin));

    // le temps est divisé par 2
    return 0;
}

void recherche_simple(int tab[], int d, int n, int size)
{
    for (size_t i = d; i < size; i++)
    {
        if (tab[i] == n)
        {
            printf("(%d, %d ) ", i, tab[i]);
        }
        usleep(10000);
    }
}

void recherche_parallele(int tab[], int n, int size)
{
    pid_t proc = fork();
    if (proc == -1)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (proc != 0)
    {
        recherche_simple(tab, 0, n, size / 2);
        int r;
        waitpid(proc, &r, 0);
    }
    else
    {
        recherche_simple(tab, size / 2, n, size);
        exit(0);
    }
}