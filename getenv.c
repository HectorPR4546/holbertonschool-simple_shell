#include "hsshell.h"

/**
 * custom_getenv - Custom implementation of getenv
 * @name: Environment variable name
 * Return: Value or NULL if not found
 */
char *custom_getenv(const char *name)
{
	char **env = environ;
	size_t len = strlen(name);

	if (!name || !*name || !env)
		return (NULL);

	while (*env)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}
