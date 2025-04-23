#include "hsshell.h"

/**
 * main - User Imput Prompt
 * Return: 0 (succcess)
 */

int main(void)
{
	int imput;
	char *line = NULL;
	size_t len = 0;
	char *token;
	char *delim = " \n";
	char *line_arg[1024];
	int pid;

	while (1)
	{
		write(1, "$ ", 2);
		imput = getline(&line, &len, stdin);

		if (imput == -1)
		{
			perror("Imput error");
			return (-1);
		}
		else if (imput == 1)
		{
			continue;
		}
		else
		{
			int idx = 0;

			token = strtok(line, delim);

			while (token != NULL)
			{
				line_arg[idx] = token;
				token = strtok(NULL, delim);
				idx++;
			}
			line_arg[idx] = NULL;

				pid = fork();

				if (pid == -1)
				{
					perror("Fork not working");
					free(line);
					return (-1);
				}
				else if (pid == 0)
				{
					char *cmdPth = pth_check(line_arg[0]);

					if (cmdPth != NULL)
					{
						execve(cmdPth, line_arg, __environ);

						perror("Fail to run");
						free(line);
						exit(1);
					}
				}
					else
					{
						int stat;

						waitpid(pid, &stat, 0);

						if (WIFEXITED(stat) && WEXITSTATUS(stat) != 0)
						{
							printf("Child proc %d exited with non zero stat %d\n,", pid, WEXITSTATUS(stat));
						}
					}
		}
	}
	free(line);
	return (0);
}

