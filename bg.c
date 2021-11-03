#include "header.h"
void bg(char *token)
{
	int arg;
	token = strtok(token + strlen(token) + 1, " \n");
	if (token == NULL)
	{
		perror("Less number of arguments passed\n");
		return;
	}
	sscanf(token, "%d", &arg);
	token = strtok(token + strlen(token) + 1, " \n");
	if (token != NULL)
	{
		perror("More number of arguments entered than required");
		return;
	}
	if (arg > onjobs)
	{
		perror("Enter valid job number\n");
		return;
	}
	int c = 0;
	int f = 0;
	int j;
	lp(i, 0, onjobs)
	{
		if (fbjobs[i].status == 0)
			c++;
		if (c == arg)
		{
			f = 1;
			j = i;
			break;
		}
	}
	if (f == 0)
	{
		perror("Invalid argument\n");
		return;
	}
	kill(fbjobs[j].pid, SIGCONT);
}