/*
* Демонстрация функций strerror и perror
*/

#include <apue.h>
#include "apue.c"
#include <errno.h>

int main(int argc, char const *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    fprintf(stderr, "EAGAIN: %s\n", strerror(EAGAIN));
    fprintf(stderr, "ENFILE: %s\n", strerror(ENFILE));
    fprintf(stderr, "ENOBUFS: %s\n", strerror(ENOBUFS));
    fprintf(stderr, "ENOLCK: %s\n", strerror(ENOLCK));
    fprintf(stderr, "ENOSPC: %s\n", strerror(ENOSPC));
    fprintf(stderr, "ENOSR: %s\n", strerror(ENOSR));
    fprintf(stderr, "EWOULDBLOCK: %s\n", strerror(EWOULDBLOCK));
    fprintf(stderr, "ENOMEM: %s\n", strerror(ENOMEM));
    fprintf(stderr, "EBUSY: %s\n", strerror(EBUSY));
    fprintf(stderr, "EINTR: %s\n", strerror(EINTR));
    errno = ENOENT;
    perror(argv[0]);

    return 0;
}
