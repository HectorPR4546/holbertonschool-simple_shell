#include "hsshell.h"

/**
 * pth_check - Find the Path
 * @cmd: Takes token argument
 * Return: 0 or all_path (success)
 */
char *pth_check(char *cmd)
{
	char *path = getenv("PATH");
	char *path_dup = strdup(path);

	char *dir = strtok(path_dup, ":");

	char *all_path = malloc(strlen(dir) + strlen(cmd) + 2);

	while (dir != NULL)
	{
		sprintf(all_path, "%s/%s", dir, cmd);
		printf("The path is %s", all_path);
		if (access(all_path, X_OK) == 0)
		{
			return (all_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_dup);
	return (all_path);
}
