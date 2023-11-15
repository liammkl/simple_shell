#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "$ "

void simple_shell(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters;
	pid_t pid;

	while (1)
	{
		printf("%s", PROMPT);
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				free(buffer);
				exit(EXIT_SUCCESS);
			} else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}
		buffer[characters - 1] = '\0';
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execlp(buffer, buffer, (char *)NULL) == -1)
			{
				perror(buffer);
				exit(EXIT_FAILURE);
			}
		} else
		{
			wait(NULL);
		}
	}
	free(buffer);
}
