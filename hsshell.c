#include "hsshell.h"

/**
 * is_empty - Checks if string is empty (only spaces/tabs/newlines)
 * @str: String to check
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

/**
 * handle_builtins - Handles builtin commands
 * @args: Command arguments
 * @line: Input line for cleanup
 * Return: 1 if builtin handled, 0 otherwise
 */
int handle_builtins(char **args, char *line)
{
	if (strcmp(args[0], "cd") == 0)
	{
		built_cd(args[1]);
		return (1);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		built_exit();
	}
	return (0);
}

/**
 * execute_child - Handles child process execution
 * @args: Command arguments
 * @line: Input line for cleanup
 */
void execute_child(char **args, char *line)
{
	char *cmdPth;

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

/**
 * execute_command - Executes a command
 * @args: Command arguments
 * @line: Input line for cleanup
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **args, char *line)
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		free(line);
		return (-1);
	}

	if (pid == 0)
		execute_child(args, line);
	else
		waitpid(pid, NULL, 0);

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

		if (imput == 1 || is_empty(line))
			continue;

		parse_input(line, line_arg);

		if (line_arg[0] == NULL)
			continue;

		if (!handle_builtins(line_arg, line))
			execute_command(line_arg, line);
	}
	free(line);
	return (0);
}
