#include "hsshell.h"

/**
 * pth_check - Finds command in PATH
 * @cmd: Command to find
 * Return: Full path or NULL
 */
char *pth_check(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy, *dir;
	char full_path[1024];

	/* Handle empty PATH or PATH not set */
	if (!path || path[0] == '\0')
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
