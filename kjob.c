#include "header.h"
void kjob(char *token)
{
	char arg1[8];
	char arg2[8];
	int tpid, sig;
	token = strtok(token + strlen(token) + 1, " \n");
	if (token == NULL)
	{
		perror("Less number of Arguments passed\n");
		return;
	}
	strcpy(arg1, token);
	token = strtok(token + strlen(token) + 1, " \n");
	if (token == NULL)
	{
		perror("Less number of Arguments passed\n");
		return;
	}
	strcpy(arg2, token);
	token = strtok(token + strlen(token) + 1, " \n");
	if (token != NULL)
	{
		perror("More number of Arguments passed than required\n");
		return;
	}
	sscanf(arg1, "%d", &tpid);
	sscanf(arg2, "%d", &sig);
	int j = 2000;
	int c = 0;
	lp(i, 0, onjobs)
	{
		if (fbjobs[i].status == 0)
			c++;
		if (c == tpid)
		{
			j = i;
			break;
		}
	}
	if (j == 2000)
	{
		perror("Invalid Id\n");
		return;
	}
	kill(fbjobs[j].pid, sig);
	return;
}