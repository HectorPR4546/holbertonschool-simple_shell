#include "hsshell.h"

/**
 * is_empty - Checks if string is empty
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
 * parse_input - Parses input line
 * @line: Input string
 * @args: Array to store arguments
 */
void parse_input(char *line, char **args)
{
	char *token = strtok(line, " \t\n");
	int idx = 0;

	while (token != NULL && idx < MAX_ARGS - 1)
	{
		args[idx++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[idx] = NULL;
}

/**
 * main - Main shell loop
 * Return: Exit status
 */
int main(void)
{
	char *line = NULL, *args[MAX_ARGS];
	size_t len = 0;
	ssize_t read;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(status);
		}

		if (read <= 1 || is_empty(line))
			continue;

		parse_input(line, args);
		if (!args[0])
			continue;

		if (strcmp(args[0], "env") == 0)
		{
			char **env = environ;

			while (*env)
				printf("%s\n", *env++);
			continue;
		}

		status = handle_execution(args, line);
	}
	return (status);
}
