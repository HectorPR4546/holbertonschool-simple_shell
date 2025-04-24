#include "hsshell.h"

/**
 * built_cd - Changes directory
 * @args: Directory path
 */
void built_cd(char *args)
{
	char *dir = args ? args : getenv("HOME");
	char cwd[1024];

	if (!dir)
	{
		fprintf(stderr, "cd: No HOME directory\n");
		return;
	}

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");

	if (chdir(dir) != 0)
		perror("cd");
	else
		setenv("PWD", dir, 1);
}

/**
 * built_exit - Exits shell
 * @args: Exit arguments
 * @line: Input buffer
 */
void built_exit(char **args, char *line)
{
	int status = 0;

	if (args[1])
		status = atoi(args[1]);

	free(line);
	exit(status);
}
