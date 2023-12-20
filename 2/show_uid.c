/*
* Демонстрация функций strerror и perror
*/

#include <apue.h>
#include "apue.c"
#include <errno.h>

int main(int argc, char const *argv[])
{
    printf("uid = %d, gid = %d\n", getuid(), getgid());

    return 0;
}
