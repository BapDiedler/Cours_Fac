#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int lance_commande(char const *commande, char *const *args);

int main(int argc, char const *argv[])
{
    int alors_pos = 0;
    int sinon_pos = 0;
    for (size_t i = 3; i < argc; i++)
    {
        if (strcmp(argv[i], "alors") == 0)
        {
            alors_pos = i;
            argv[i] = NULL;
        }
        else if (strcmp(argv[i], "sinon") == 0)
        {
            sinon_pos = i;
            argv[i] = NULL;
        }
    }
    if (argc < 3 || strcmp(argv[1], "si") != 0)
    {
        fprintf(stderr, "Erreur situé au 'si'\n");
    }
    else
    {
        int r = lance_commande(argv[2], (char *const *)&argv[2]);
        if (!r)
        {
            lance_commande(argv[alors_pos + 1], (char *const *)&argv[alors_pos + 1]);
        }
        else if (sinon_pos != 0)
        {
            lance_commande(argv[sinon_pos + 1], (char *const *)&argv[sinon_pos + 1]);
        }
    }
    return 0;
}

int lance_commande(char const *commande, char *const *args)
{
    int r;
    pid_t proc = fork();
    if (proc == -1)
    {
        fprintf(stderr, "fork failed\n");
    }
    else if (proc == 0)
    {
        execvp(commande, args);
        fprintf(stdout, "execlp() : %s\n", errno);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(proc, &r, 0);
    }
    return r;
}