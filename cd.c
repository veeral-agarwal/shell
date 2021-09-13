#include "headers.h"
void cd(char *token, char argument[])
{
	token = strtok (token + strlen (token) + 1, " ");
	if (token == NULL)
	{
		chdir(root);
		return;
	}
	int c = 0;
	while (token[c] == ' ')
		c++;
	lp(i, c, strlen(token) - 1)
	{
		argument[i - c] = token[i];
	}
	argument[strlen(token) - c - 1] = '\0';
	// printf("%d\n", strlen(argument));
	token = strtok (token + strlen (token) + 1, " ");
	if (token != NULL)
	{
		printf("Error: Two many arguments\n");
		return;
	}
	else
	{
		int d;
		if (strcmp(argument, "..") == 0)
		{
			if (nested_count == 0)
			{
				chdir(argument);
				// printf("%s\n", root);
			}
			else
			{
				nested_count--;
				chdir(argument);
			}
		}
		else if (strcmp(argument, "~") == 0)
		{
			nested_count = 0;
			chdir(root);
		}
		else
		{
			d = chdir(argument);
			if (d == -1)
			{
				printf("Error: No such file or directory\n");
				return;
			}
			else
			{
				nested_count++;
			}
		}
	}
	handleonjobs();
}
