#include "hsshell.h"

/**
 * pth_check - Finds command in PATH
 * @cmd: Command to find
 * Return: Full path or NULL
 */
char *pth_check(char *cmd)
{
	char *path = custom_getenv("PATH");
	char *path_copy, *dir;
	char full_path[1024];
	struct stat st;

	if (!path)
		return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
