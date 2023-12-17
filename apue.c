#include "apue.h"
#include <errno.h>  /* определение переменной errno*/
#include <stdarg.h> /* список аргументов переменной длины ISO C*/

static void err_doit(int, int, const char *, va_list);

/*
 * Обрабатывает фатальные ошибки, не связанные с системными вызовами.
 * Выводит сообщение и завершает работу процесса.
 */
void err_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
 * Обрабатывает фатальные ошибки, связанные с системными вызовами.
 * Выводит сообщение и завершает работу процесса.
 */
void err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    exit(1);
}

/*
 * Выводит сообщение и возвращает управление в вызывающую функцию.
 * Вызывающая функция определяет значение флага "errnoflag".
 */
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflag)
    {
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
    }
    strcat(buf, "\n");
    fflush(stdout); /* в случае когда stdout и stderr - одно и то же устройство */
    fputs(buf, stderr);
    fflush(NULL); /* сбрасывает все выходные потоки */
}