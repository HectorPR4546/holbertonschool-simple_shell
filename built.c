#include "hsshell.h"

/**
 * built_cd - cd command
 * @args: arguments
 */
void built_cd(char *args)
{
	char *dir = args;
	char *home = getenv("HOME");

	if (dir == NULL)
		dir = home;

	if (dir == NULL)
	{
		perror("cd: No HOME directory");
		return;
	}

	if (chdir(dir) != 0)
		perror("cd");
}

/**
 * built_exit - exit command
 */
void built_exit(void)
{
	exit(0);
}
