#include "header.h"
void unSetEnv(char *token)
{
	char arg[100];
	token = strtok(token + strlen(token) + 1, " ");
	if (token == NULL)
	{
		perror("Less Number of values entered\n");
		return;
	}
	else
		strcpy(arg, token);
	token = strtok(token + strlen(token) + 1, " ");
	if (token != NULL)
	{
		perror("More number of values entered than required\n");
		return;
	}
	if (unsetenv(arg) != 0)
	{
		perror("unsetenv failed\n");
		return;
	}
}