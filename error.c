#include "hsshell.h"

/**
 * error_ms - Prints command error
 * @cmd: Failed command
 */
void error_ms(char *cmd)
{
	char error[256];
	int len = snprintf(error, sizeof(error), "./hsh: 1: %s: not found\n", cmd);

	write(STDERR_FILENO, error, len);
}
