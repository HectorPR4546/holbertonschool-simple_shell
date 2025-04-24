#include "hsshell.h"

/**
 * handle_builtins - Handles builtin commands
 * @args: Command arguments
 * @line: Input buffer
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
		built_exit(args, line);
	}
	return (0);
}

/**
 * execute_child - Handles child process execution
 * @args: Command arguments
 * @line: Input buffer
 */
static void execute_child(char **args, char *line)
{
	char *cmd_path;
	struct stat st;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == 0 && (st.st_mode & S_IXUSR))
		{
			execve(args[0], args, environ);
		}
	}
	else
	{
		cmd_path = pth_check(args[0]);
		if (cmd_path)
		{
			execve(cmd_path, args, environ);
			free(cmd_path);
		}
	}
	error_ms(args[0]);
	free(line);
	exit(127);
}

/**
 * handle_execution - Handles command execution
 * @args: Command arguments
 * @line: Input buffer
 * Return: Exit status
 */
int handle_execution(char **args, char *line)
{
	pid_t pid;
	char *cmd_path;
	struct stat st;

	if (handle_builtins(args, line))
		return (0);

	/* Check if command exists before forking */
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == -1 || !(st.st_mode & S_IXUSR))
		{
			error_ms(args[0]);
			return (127);
		}
	}
	else
	{
		cmd_path = pth_check(args[0]);
		if (!cmd_path)
		{
			error_ms(args[0]);
			return (127);
		}
		free(cmd_path);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		execute_child(args, line);
	else
		waitpid(pid, NULL, 0);
	return (0);
}
