#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PERM_644 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

int main(int argc, char const *argv[])
{
    pid_t proc = fork();
    if (proc == -1)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (proc != 0)
    {
        int r;
        waitpid(proc, &r, 0);
        if (r == 0)
        {
            printf("ls s'est bien terminé\n");
        }
    }
    else
    {
        int newout = open("stdout.txt", O_WRONLY | O_CREAT, 0644);
        dup2(newout, STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    }
    return 0;
}
