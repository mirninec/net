/*
 * Копирование стандартного ввода в стандартный вывод с использованием
 * стандартных функций ввода/вывода
 */

#include <apue.h>
#include "apue.c"

int main(int argc, char const *argv[])
{
    int c;

    while ((c = getc(stdin)) != EOF)
    {
        if(putc(c, stdout) == EOF)
            err_sys("ошибка ввода");
    }

    if(ferror(stdin))
        err_sys("ошибка ввода");
    
    return 0;
}
