/*
* Проверка возможности свободного перемещения текущей позици в файле стандартного ввода
* листинг 3.1
*/
#include <apue.h>
#include "apue.c"

int main(int argc, char const *argv[])
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
        printf("перемещение невозможно\n");
    else 
        printf("перемещение выполнено\n");
    return 0;
}
