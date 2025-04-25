#include "hsshell.h"

static int command_status;

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
		command_status = 0;
		return (1);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		built_exit(args, line, command_status);
		return (1);
	}
	return (0);
}

/**
 * validate_command - Checks command validity
 * @args: Command arguments
 * Return: Status code
 */
static int validate_command(char **args)
{
	struct stat st;
	char *cmd_path;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (stat(args[0], &st) == -1 || !(st.st_mode & S_IXUSR))
		{
			error_ms(args[0]);
			return (2);
		}
		return (0);
	}

	cmd_path = pth_check(args[0]);
	if (!cmd_path)
	{
		error_ms(args[0]);
		return (127);
	}
	free(cmd_path);
	return (0);
}

/**
 * run_child_process - Executes command in child
 * @args: Command arguments
 * @line: Input buffer
 */
static void run_child_process(char **args, char *line)
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
 * handle_execution - Main execution handler
 * @args: Command arguments
 * @line: Input buffer
 * Return: Exit status
 */
int handle_execution(char **args, char *line)
{
	pid_t pid;
	int current_status;

	if (handle_builtins(args, line))
		return (command_status);

	current_status = validate_command(args);
	if (current_status != 0)
	{
		command_status = current_status;
		return (current_status);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
		run_child_process(args, line);

	waitpid(pid, &current_status, 0);
	command_status = WIFEXITED(current_status) ? WEXITSTATUS(current_status) : -1;
	return (command_status);
}
