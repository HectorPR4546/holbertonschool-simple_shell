#include "hsshell.h"

/**
 * error_ms - Error ms
 * @cmd: Command
 */
void error_ms(char *cmd)
{
	char *error_ms;
	char *error_ms2;

	error_ms = "cmd '";

	write(STDERR_FILENO, error_ms, strlen(error_ms));
	write(STDERR_FILENO, cmd, strlen(cmd));

	error_ms2 = "' not found\n";

	write(STDERR_FILENO, error_ms2, strlen(error_ms2));
	exit(EXIT_FAILURE);
}
