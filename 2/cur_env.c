#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *encoding = getenv("LANG");
    if (encoding != NULL)
    {
        printf("Текущая кодировка консоли: %s\n", encoding);
    }
    else
    {
        printf("Не удалось получить текущую кодировку консоли\n");
    }
    return 0;
}
