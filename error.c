#include "hsshell.h"

/**
 * error_ms - Error message
 * @cmd: Command
 */
void error_ms(char *cmd)
{
	char *msg = ": not found\n";

	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, msg, strlen(msg));
}
