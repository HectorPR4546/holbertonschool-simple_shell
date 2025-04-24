#include "hsshell.h"

/**
 * handle_builtins - Handles builtin commands
 * @args: Command arguments
 * @line: Input buffer
 * Return: 1 if builtin handled, 0 otherwise
 */
static int handle_builtins(char **args, char *line)
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
 * check_command_exists - Checks if command exists before forking
 * @args: Command arguments
 * @line: Input buffer
 * Return: 1 if exists, 0 if not
 */
static int check_command_exists(char **args, char *line)
{
	char *cmd_path;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], X_OK) == -1)
		{
			error_ms(args[0]);
			free(line);
			return (0);
		}
		return (1);
	}

	cmd_path = pth_check(args[0]);
	if (!cmd_path)
	{
		error_ms(args[0]);
		free(line);
		return (0);
	}
	free(cmd_path);
	return (1);
}

/**
 * execute_child - Handles child process execution
 * @args: Command arguments
 * @line: Input buffer
 */
static void execute_child(char **args, char *line)
{
	char *cmd_path;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		execve(args[0], args, environ);
	}
	else
	{
		cmd_path = pth_check(args[0]);
		execve(cmd_path, args, environ);
		free(cmd_path);
	}
	error_ms(args[0]);
	free(line);
	exit(127);
}

/**
 * handle_execution - Handles command execution
 * @args: Command arguments
 * @line: Input buffer
 * Return: 0 on success, -1 on failure
 */
int handle_execution(char **args, char *line)
{
	pid_t pid;

	if (handle_builtins(args, line))
		return (0);

	/* Check command exists before forking */
	if (!check_command_exists(args, line))
		return (127);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(line);
		return (-1);
	}
	if (pid == 0)
		execute_child(args, line);
	else
		waitpid(pid, NULL, 0);
	return (0);
}
