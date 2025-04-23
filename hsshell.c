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
	char *delim = " ";

	write(1, "$ ", 2);
	imput = getline(&line, &len, stdin);

	if (imput == -1)
	{
		perror("Imput error");
		return (-1);
	}
	else
	{
		token = strtok(line, delim);

		while (token != NULL)
		{
			pid_t pid;

			pid = fork();

			if (pid == -1)
			{
				perror("Fork not working");
				return (-1);
			}
			else if (pid == 0)
			{
				char *cmdPth = pth_check(token);

				if (cmdPth == NULL)
				{
					perror("Command not listed");
					exit(1);
				}

				execve(cmdPth, &token, __environ);

				if (execve(cmdPth, &token, __environ) == -1)
				{
					perror("Fail to run");
					exit(EXIT_FAILURE);
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
			token = strtok(NULL, delim);
		}
		return (0);
	}
}
