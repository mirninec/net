/*
 * Вывод идентификатора процесса
 */

#include <apue.h>
#include "apue.c"

int main(int argc, char const *argv[])
{
    printf("Привет от процесса с идентификатором %d\n", getpid());
    exit(0);
}
