#include "hsshell.h"

/**
 * error_ms - Prints command error
 * @cmd: Failed command
 */
void error_ms(char *cmd)
{
	char *msg = ": not found\n";

	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, msg, strlen(msg));
}
