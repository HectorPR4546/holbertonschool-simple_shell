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
	char line_arg[1024];
	char *dir = strtok(path_dup, ":");

	while (dir != NULL)
	{
		strcpy(line_arg, dir);
		if (line_arg[strlen(line_arg) - 1] != '/')
		{
			strcat(line_arg, "/");
		}


		strcat(line_arg, cmd);

		if (access(line_arg, F_OK) == 0 && access(line_arg, X_OK) == 0)
		{
			free(path_dup);
			return (strdup(line_arg));
		}
		dir = strtok(NULL, ":");
	}
	printf("File not found\n");
	free(path_dup);
	return (NULL);
}
