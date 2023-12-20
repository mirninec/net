#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    long max_open_files = sysconf(_SC_OPEN_MAX);
    if (max_open_files != -1)
    {
        printf("Максимальное количество открытых файлов: %ld\n", max_open_files);
    }
    else
    {
        perror("Ошибка при получении информации о максимальном количестве открытых файлов");
    }
    return 0;
}
