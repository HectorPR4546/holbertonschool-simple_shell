#include "hsshell.h"

/**
 * built_cd - cd command
 * @args: arguments
 * Return: 0 Success or -1 fail
 */
void built_cd(char *args)
{
	if (args == NULL)
	{
		char *home = getenv("HOME");

		if (home == NULL)
		{
			perror("cd: HOME env is not set\n");
		}
		else
		{
			if (chdir(home) != 0)
			{
				perror("Fail to change directory");
			}
		}
	}
	else
	{
		if (chdir(args) != 0)
		{
			perror("Fail to change directory");
		}
	}
}

/**
 * built_exit - exit command
 */
void built_exit(void)
{
	printf("\nExit hsshell...\n");
	exit(0);
}
