#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void exercice2_1();
void exercice2_2();

int main(int argc, char const *argv[])
{
    exercice2_1();
    exercice2_2();
    return 0;
}


void exercice2_1()
{
    printf("Bonjour\n");
    sleep(5);
    printf("Au revoir\n");
}

void exercice2_2()
{
    pid_t proc = fork();
    if (proc == -1)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (proc != 0)
    {
        printf("%d:père\n", getpid());
        sleep(5);
        int r;
        waitpid(proc, &r, 0);
    }
    else
    {
        printf("%d:fils\n", getpid());
        sleep(2);
    }
}