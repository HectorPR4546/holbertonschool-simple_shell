#include "hsshell.h"

void Bet_bypass(void);

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
			if (feof(stdin))
			{
				built_exit();
			}
			else
			{
				perror("Imput error");
				return (-1);
			}
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

			if (strcmp(line_arg[0], "cd") == 0)
			{
				built_cd(line_arg[1]);
			}
			else if (strcmp(line_arg[0], "exit") == 0)
			{
				built_exit();
			}
			else
			{
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
						execve(cmdPth, line_arg, environ);
						error_ms(line_arg[0]);
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
						printf("Child proc %d\n,", pid);
					}
				}
			}
		}
	}
	free(line);
	return (0);
}
