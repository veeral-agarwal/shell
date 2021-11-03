#include "header.h"
void setEnv(char *token)
{
	char arg1[100];
	char arg2[100];
	lp(i, 0, 100)
	{
		arg1[i] = '\0';
		arg2[i] = '\0';
	}
	token = strtok(token + strlen(token) + 1, " \n");
	// printf("%s\n", token);
	if (token == NULL)
	{
		printf("Less number of values entered\n");
		return;
	}
	strcpy(arg1, token);
	token = strtok(token + strlen(token) + 1, " \n");
	int f = 0;
	if (token == NULL)
	{
		f = 1;
		// printf("awda\n");
		arg2[0] = '\0';
	}
	else
		strcpy(arg2, token);
	if (f == 0)
	{
		token = strtok(token + strlen(token) + 1, " \n");
		if (token != NULL)
		{
			printf("More values have been entered");
			return;
		}
	}
	if (f)
	{
		printf("wa\n");
		if (setenv(arg1, "", 1) == -1)
		{
			perror("Setenv failed\n");
		}
	}
	else
	{
		if (setenv(arg1, arg2, 1) == -1)
		{
			perror("Setenv failed\n");
		}
	}
}