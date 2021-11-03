#include "header.h"
void execpipe(char arr[])
{
	int stdin = 0, stdout = 1;
	int len = strlen(arr);
	int c = 0;
	lp(i, 0, len)
	{
		if (arr[i] == '|')
			c++;
	}
	if (c == 0)
	{
		// printf("dawdawd\n");
		// printf("%s", arr);
		command_handler(arr);
		return;
	}
	char tokens[c + 1][100];
	char *ptr = strtok(arr, "|\n");
	lp(i, 0, c + 1)
	{
		strcpy(tokens[i], ptr);
		ptr = strtok(NULL, "|\n");
	}
	int fdes[20][2];
	stdout = dup(1);
	stdin = dup(0);
	lp(i, 0, c + 1)
	{
		if (pipe(fdes[i]) < 0) //change
		{
			perror("Pipe Failed!!\n");
			exit(0);
		}
		if (i == 0)
		{
			dup2(fdes[i][1], 1);
			close(fdes[i][1]);
		}
		else if (i == c)
		{
			// close(fdes[1]);
			dup2(fdes[i - 1][0], 0);
			dup2(stdout, 1);
			close(fdes[i - 1][0]);
		}
		else
		{
			dup2(fdes[i - 1][0], 0);
			dup2(fdes[i][1], 1);
			close(fdes[i - 1][0]);
			close(fdes[i][1]);
		}
		int pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			exit(0);
		}
		if (pid == 0)
		{
			command_handler(tokens[i]);
			exit(0);
		}
		else
		{
			// int status;
			// waitpid(pid, &status, 0);
			wait(NULL);
			// printf("twad\n");
			dup2(stdin, 0);
			dup2(stdout, 1);
		}
		// printf("taw\n");
	}
}