/*
 * Чтение команд со стандартного ввода и их выполнение
 */

#include <apue.h>
#include "apue.c"
#include <sys/wait.h>

static void sig_int(int); /* наша функция-перехватчик */

int main(void)
{
    char buf[MAXLINE]; /* из apue.h */
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("ошибка вызова signal");

    printf("%% "); /* вывести приглашение (printf требует использовать последовательность %%, чтобы вывести символ %)*/

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0; /* заменить символ перевода строки */
            // printf("Введена команда: %s\n", buf);
        }
        if ((pid = fork()) < 0)
        {
            err_sys("ошибка вызова fork()");
        }
        else if (pid == 0)
        { /* дочерний процесс */
            // execlp(buf, buf, (char *)0);
            execlp(buf, buf, NULL);
            err_ret("невозможно выполнить_: %s", buf);
            exit(127);
        }

        /* родительский процесс */
        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("ошибка вызова waitpid");
        printf("%% ");
    }
    exit(0);
}

void sig_int(int signo)
{
    printf("прервано\n%% ");
}
