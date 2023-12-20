#include "apue.h"
#include "apue.c"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);

int
main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("Использование: a.out <dirname>");

	exit(0);
}

static void
pr_sysconf(char *mesg, int name)
{
	long val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = sysconf(name)) < 0) {
		if (errno != 0) {
			if (errno = EINVAL)
				fputs(" (не поддерживается)\n", stdout);
			else
				err_sys("ошибка вызова sysconf");
		}
	} else {
		printf(" %ld\n", val); 
	}
}

static void
pr_pathconf(char *mesg, char *path, int name)
{
	long val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = pathconf(path, name)) < 0) {
		if (errno != 0) {
			if (errno == EINVAL)
				fputs(" (не поддерживается)\n", stdout);
			else
				err_sys("ошибка вызова pathconf, path = %s", path);
		} else {
			fputs(" (нет ограничений)\n", stdout);
		}
	} else {
		printf(" %ld\n", val);
	}
}

