/*
* Определение количества файловых дескрипторов
* листинг 2.4
*/

#include <apue.h>
#include "apue.c"
#include <limits.h>
#include <unistd.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else 
static long openmax = 0;
#endif
/*
 * Если константа PATH_MAX не определена
 * адекватность следующего числа не гарантируется
 */
#define OPEN_MAX_GUESS 1024

long open_max(void)
{
    if(openmax == 0) { /* первый вызов функции */
        errno = 0;
        if((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
            if(errno == 0)
                openmax = OPEN_MAX_GUESS; /* неопределенный предел */
            else    
                err_sys("ошибка вызова sysconf с параметром _SC_OPEN_MAX");
        }
    }
    return(openmax);
}

 int main(int argc, char const *argv[])
{
    printf("%ld\n",open_max());
    printf("%ld\n",pathconf("./copy.c", _PC_NAME_MAX));
    printf("_POSIX_NO_TRUNC %ld\n", sysconf(_POSIX_NO_TRUNC));
    return 0;
}
