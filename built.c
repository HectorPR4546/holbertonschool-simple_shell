#include "hsshell.h"

/**
 * built_cd - Changes directory
 * @args: Directory path
 */
void built_cd(char *args)
{
	char *dir = args ? args : getenv("HOME");

	if (!dir)
	{
		perror("cd: No HOME");
		return;
	}

	if (chdir(dir) != 0)
		perror("cd");
}

/**
 * built_exit - Exits shell
 */
void built_exit(void)
{
	exit(0);
}
