#include "hsshell.h"

/**
 * built_cd - Changes directory
 * @args: Directory path
 */
void built_cd(char *args)
{
	char *dir = args ? args : custom_getenv("HOME");
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
 * built_exit - Exits shell with status
 * @args: Exit arguments
 * @line: Input buffer
 * @last_status: Status of last command
 */
void built_exit(char **args, char *line, int last_status)
{
	int status = args[1] ? atoi(args[1]) : last_status;

	free(line);
	exit(status);
}
