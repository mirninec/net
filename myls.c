#include <apue.h>
#include "apue.c"
#include <dirent.h>

int main(int argc, char const *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc < 2)
        err_quit("Использование: ls имя_каталога");

    if ((dp = opendir(argv[1])) == NULL)
        err_sys("невозможно открыть %s", argv[1]);
    while ((dirp = readdir(dp)) != NULL)
    {
        printf("%s\t\t%ld\t%d\n", dirp->d_name, dirp->d_ino, dirp->d_type);
    }

    closedir(dp);
    return 0;
}