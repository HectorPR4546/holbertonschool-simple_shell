#include "hsshell.h"

/**
 * parse_input - Token the input line into arguments
 * @line: Input line from user
 * @args: Array of command and its arguments
 */
void parse_input(char *line, char **args)
{
	int i = 0;
	char *token;

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;
}

