#include "apue.h"
#include <errno.h>  /* определение переменной errno*/
#include <stdarg.h> /* список аргументов переменной длины ISO C*/
#include <syslog.h>

static void err_doit(int, int, const char *, va_list);

/*
 * Обрабатывает нефатальные ошибки, связанные с системными вызовами.
 * Выводит сообщение и возвращает управление.
 */
void err_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
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
 * Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
 * Код ошибки передает в аргуметне.
 * Выводит сообщение и возвращает управление.
 */
void err_cont(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
}

/*
 * Обрабатывает фатальные ошибки, не связанные с системными вызовами.
 * Код ошибки передается в аргументе.
 * Выводит сообщение и завершает работу процесса.
 */
void err_exit(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}

/*
 * Обрабатывает фатальные ошибки, связанные с системными вызовами.
 * Выводит сообщение, создает файл core и завершает работу процесса.
 */
void err_dump(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort(); /* записать дамп памяти в файл и завершить процесс */
    exit(1); /* этот вызов никогда не должен выполниться */
}

/*
 * Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
 * Выводит сообщение и возвращает управление.
 */
void err_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}

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

/*
 * Процедуры обработки ошибок для программ, которые могут работать как демоны.
 */

static void err_doit(int, int, const char *, va_list);

/*
 * В вызывающем процессе должна быть определена и установлена эта переменная:
 * ненулевое значение - для интерактивных программ, нулевое - для демонов
 */
extern int log_to_stderr;

/*
 * Инициализировать syslog(), если процесс работает в режиме демона.
 */
void log_open(const char *ident, int option, int facility)
{
    if (log_to_stderr == 0)
        openlog(ident, option, facility);
}

/*
 * Обрабатывает нефатальные ошибки, связанные с системными вызовами.
 * Выводит сообщение, соответствующее содержимому переменной errno,
 * и возвращает управление.
 */
void log_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
}

/*
 * Обрабатывает фатальные ошибки, связанные с системными вызовами.
 * Выводит сообщение и завершает работу процесса.
 */
void log_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*
 * Обрабатывает нефатальные ошибки, не связанные с системными вызовами.
 * Выводит сообщение и возвращает управление.
 */
void log_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
}

/*
 * Обрабатывает фатальные ошибки, не связанные с системными вызовами.
 * Выводит сообщение и завершает работу процесса.
 */
void log_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*
 * Обрабатывает фатальные ошибки, связанные с системными вызовами.
 * Номер ошибки передается в параметре.
 * Выводит сообщение и завершает работу процесса.
 */
void log_exit(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, error, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*
 *  Выводит сообщение и возвращает управление в вызывающую функуцию.
 * Вызывающая функция должна определить значение аргументов
 * "errnoflag" и "priority".
 */
static void log_doit(int errnoflag, int error, int priority, const char *fmt, va_list ap)
{
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflag)
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
    strcat(buf, "\n");
    if (log_to_stderr)
    {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }
    else
    {
        syslog(priority, "%s", buf);
    }
}