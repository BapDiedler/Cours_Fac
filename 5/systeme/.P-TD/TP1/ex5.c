#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void sig_handler1(int sig);

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_handler1);
    pid_t proc = fork();
    if (proc == -1)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (proc != 0)
    {
        sleep(10);
    }
    else
    {
        sleep(5);
        kill(getppid(), SIGINT);
        exit(0);
    }
    return 0;
}

void sig_handler1(int sig)
{
    printf("Au revoir\n");
    exit(EXIT_SUCCESS);
}