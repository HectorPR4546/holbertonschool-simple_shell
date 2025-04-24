#include "hsshell.h"

/**
 * built_cd - Changes directory
 * @args: Directory path
 */
void built_cd(char *args)
{
	char *dir = args ? args : _getenv("HOME");
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
	{
		char *new_pwd = getcwd(cwd, sizeof(cwd));

		if (new_pwd)
		{
			char pwd_var[1024];

			snprintf(pwd_var, sizeof(pwd_var), "PWD=%s", new_pwd);
			putenv(strdup(pwd_var));
		}
	}
}

/**
 * built_exit - Exits shell with status
 * @args: Command arguments
 * @line: Input buffer
 * @last_status: Status of last command
 */
void built_exit(char **args, char *line, int last_status)
{
	int status = args[1] ? atoi(args[1]) : last_status;

	free(line);
	exit(status);
}
