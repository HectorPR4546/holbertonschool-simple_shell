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
	char *token = strtok(line, " \n");
	int idx = 0;

	while (token != NULL && idx < 1023)
	{
		args[idx++] = token;
		token = strtok(NULL, " \n");
	}
	args[idx] = NULL;
}

/**
 * main - Main shell loop
 * Return: Exit status
 */
int main(void)
{
	char *line = NULL, *args[1024];
	size_t len = 0;
	ssize_t read;

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
			exit(0);
		}

		if (read <= 1 || is_empty(line))
			continue;

		parse_input(line, args);
		if (!args[0])
			continue;

		handle_execution(args, line);
	}
	return (0);
}
