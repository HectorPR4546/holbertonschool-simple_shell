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
 * check_command_exists - Validates if command exists and is executable
 * @args: Command arguments
 * Return: 1 if exists and executable, 0 otherwise
 */
static int check_command_exists(char **args)
{
	struct stat st;
	char *cmd_path;

	if (args[0][0] == '/' || args[0][0] == '.')
		return (stat(args[0], &st) == 0 && (st.st_mode & S_IXUSR));

	cmd_path = pth_check(args[0]);
	if (cmd_path)
	{
		free(cmd_path);
		return (1);
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

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		execve(args[0], args, environ);
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
 * fork_and_execute - Forks process and executes command
 * @args: Command arguments
 * @line: Input buffer
 * Return: Exit status of child process
 */
static int fork_and_execute(char **args, char *line)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		execute_child(args, line);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

/**
 * handle_execution - Handles command execution
 * @args: Command arguments
 * @line: Input buffer
 * Return: Exit status
 */
int handle_execution(char **args, char *line)
{
	if (handle_builtins(args, line))
		return (0);

	if (!check_command_exists(args))
	{
		error_ms(args[0]);
		return (127);
	}

	return (fork_and_execute(args, line));
}
