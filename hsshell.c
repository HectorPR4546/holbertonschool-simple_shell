#include "hsshell.h"

/**
 * parse_input - Parse user input into arguments
 * @line: Input line
 * @args: Array to store arguments
 */
void parse_input(char *line, char **args)
{
	char *token;
	char *delim = " \n";
	int idx = 0;

	token = strtok(line, delim);
	while (token != NULL)
	{
		args[idx] = token;
		token = strtok(NULL, delim);
		idx++;
	}
	args[idx] = NULL;
}

/**
 * execute_command - Execute a command
 * @args: Command and arguments
 * @line: Input line for cleanup
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args, char *line)
{
	int pid;
	char *cmdPth;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		free(line);
		return (-1);
	}

	if (pid == 0)
	{
		if (args[0][0] == '/' || args[0][0] == '.')
		{
			cmdPth = args[0];
			if (access(cmdPth, X_OK) == -1)
			{
				error_ms(args[0]);
				free(line);
				exit(127);
			}
		}
		else
		{
			cmdPth = pth_check(args[0]);
			if (cmdPth == NULL)
			{
				error_ms(args[0]);
				free(line);
				exit(127);
			}
		}

		execve(cmdPth, args, environ);
		error_ms(args[0]);
		free(line);
		exit(127);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (0);
}

/**
 * main - User Input Prompt
 * Return: 0 (success)
 */
int main(void)
{
	int imput;
	char *line = NULL;
	size_t len = 0;
	char *line_arg[1024];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);

		imput = getline(&line, &len, stdin);

		if (imput == -1)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			free(line);
			built_exit();
		}

		if (imput == 1 || strspn(line, " \n") == strlen(line))
			continue;

		parse_input(line, line_arg);

		if (strcmp(line_arg[0], "cd") == 0)
		{
			built_cd(line_arg[1]);
		}
		else if (strcmp(line_arg[0], "exit") == 0)
		{
			free(line);
			built_exit();
		}
		else
		{
			execute_command(line_arg, line);
		}
	}
	free(line);
	return (0);
}
