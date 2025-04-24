#include "hsshell.h"

/**
 * pth_check - Find the Path
 * @cmd: Takes token argument
 * Return: path or NULL
 */
char *pth_check(char *cmd)
{
	char *path = getenv("PATH");
	char *path_dup, *dir;
	char line_arg[1024];

	if (path == NULL)
		return (NULL);

	path_dup = strdup(path);
	dir = strtok(path_dup, ":");

	while (dir != NULL)
	{
		strcpy(line_arg, dir);
		strcat(line_arg, "/");
		strcat(line_arg, cmd);

		if (access(line_arg, X_OK) == 0)
		{
			free(path_dup);
			return (strdup(line_arg));
		}
		dir = strtok(NULL, ":");
	}
	free(path_dup);
	return (NULL);
}
