#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE_BUFFER 4095

static int copy_file(char const *src, char const *dst);
static int copy_folder(char const *src, char const *dst);
static char *make_path(char const *path, char const *file);
static int is_dir(char const *path);

char *buf;

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Utilisation: ./cp SOURCE DEST\n");
        return 1;
    }

    if (strcmp(argv[argc - 2], argv[argc - 1]) == 0)
    {
        return 0;
    }

    buf = (char *)malloc(SIZE_BUFFER * sizeof(char));
    struct stat statbuf;
    stat(argv[argc - 2], &statbuf);
    if (S_ISDIR(statbuf.st_mode))
    {
        // Si le répertoir existe déjà on le copie dans celui là (comportement de cp observé)
        if (access(argv[argc - 1], F_OK) == 0)
        {
            char *s = make_path(argv[argc - 1], argv[argc - 2]);
            copy_folder(argv[argc - 2], s);
            free(s);
        }
        else
        {
            copy_folder(argv[argc - 2], argv[argc - 1]);
        }
    }
    else
    {
        copy_file(argv[argc - 2], argv[argc - 1]);
    }
    free(buf);
    return 0;
}

static int overwrite_file();

static int copy_file(char const *src, char const *dst)
{
    int size;
    int f_src, f_dst;

    // Ouverture des fichiers:
    f_src = open(src, O_RDONLY);
    if (f_src < 0)
    {
        fprintf(stderr, "%s", src);
        perror("open ");
        goto error;
    }
    if (access(dst, F_OK) == 0)
    {
        printf("cp : voulez-vous écraser '%s' ? [y/n]", dst);
        if (!overwrite_file())
        {
            return 0;
        }
    }
    f_dst = open(dst, O_WRONLY | O_CREAT | O_TRUNC);
    if (f_dst < 0)
    {
        fprintf(stderr, "%s", dst);
        perror("open ");
        goto error;
    }

    // Copie du fichier
    do
    {
        size = read(f_src, buf, SIZE_BUFFER);
        write(f_dst, buf, size);
    } while (size > 0);

    // Changement droit
    struct stat sb;
    stat(src, &sb);
    chmod(dst, sb.st_mode);

    close(f_src);
    close(f_dst);
    return 0;

error:
    if (f_src < 0)
    {
        close(f_src);
    }
    if (f_src < 0)
    {
        close(f_dst);
    }
    return 1;
}

static int overwrite_file()
{
    char c = getchar();
    while (c != 'y' && c != 'n')
    {
        c = getchar();
    }
    return c == 'y';
}

static int copy_folder(char const *src, char const *dst)
{
    struct dirent *entry;
    DIR *d_src = opendir(src);
    if (d_src == NULL)
    {
        fprintf(stderr, "%s:\n", src);
        perror("d_src ");
        goto error;
    }

    if (mkdir(dst, 0755) < 0)
    {
        if (errno != EEXIST)
        {
            printf("%s\n", dst);
            perror("mkdir ");
            goto error;
        }
    }

    // Changement droit
    struct stat sb;
    stat(src, &sb);
    chmod(dst, sb.st_mode);

    // Copie des fichiers dans le dossier
    while ((entry = readdir(d_src)) != NULL)
    {
        if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0)
        {
            char *path_src = make_path(src, entry->d_name);
            char *path_dst = make_path(dst, entry->d_name);
            if (is_dir(path_src))
            {
                copy_folder(path_src, path_dst);
            }
            else
            {
                copy_file(path_src, path_dst);
            }
            free(path_src);
            free(path_dst);
        }
    }
    closedir(d_src);
    return 0;

error:
    if (d_src != NULL)
    {
        closedir(d_src);
    }
    return 1;
}

static char *make_path(char const *path, char const *file)
{
    int len_src = strlen(path) + strlen(file);
    char *path_result = (char *)malloc(len_src + 2);
    strcpy(path_result, path);
    strcat(path_result, "/");
    strcat(path_result, file);
    return path_result;
}

static int is_dir(char const *path)
{
    struct stat statbuf;
    stat(path, &statbuf);
    return S_ISDIR(statbuf.st_mode);
}
