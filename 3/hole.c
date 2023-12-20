/*
* Создание файла с "дыркой"
* листинг 3.2
*/
#include <apue.h>
#include <fcntl.h>
#include "apue.c"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char const *argv[])
{
    int fd;
    if((fd = creat("file.hole", FILE_MODE))<0)
        err_sys("ошибка вызова функции creat");
    
    if(write(fd, buf1, 10) != 10)
        err_sys("ошибка записи buf1");
    /* теперь текущая позиция 10 */
    printf("текущая позиция %ld\n", lseek(fd, 0, SEEK_CUR));

    if(lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("ошибка вызова lseek");
    /* теперь текущая позиция 16384 */
    printf("текущая позиция %ld\n", lseek(fd, 0, SEEK_CUR));

    if(write(fd, buf2, 10) != 10)
        err_sys("ошибка записи buf2");
    /* теперь текущая позиция 16394 */

    printf("текущая позиция %ld\n", lseek(fd, 0, SEEK_CUR));
    
    return 0;
}
