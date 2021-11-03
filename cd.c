#include "header.h"
void cd(char *token, char argument[])
{
	char tempdir[1024];
	getcwd(tempdir, 1024);
	token = strtok (token + strlen (token) + 1, " ");
	if (token == NULL)
	{
		chdir(root);
		return;
	}
	int c = 0;
	while (token[c] == ' ')
		c++;
	lp(i, c, strlen(token))
	{
		argument[i - c] = token[i];
	}
	// argument[strlen(token) - c - 1] = '\0';
	// printf("%s\n", argument);
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
		else if (strcmp(argument, "-") == 0)
		{
			if (strlen(prevd) == 0)
			{
				printf("No previous working directory found\n");
				return;
			}
			else
			{
				chdir(prevd);
				int f = 0;
				int x = strlen(root);
				lp(i, 0, x)
				{
					if (root[i] == prevd[i])
						continue;
					else
					{
						// printf("%d\n", i);
						f = 1;
						break;
					}
				}
				if (f == 1)
				{}
				else
				{
					int v = strlen(prevd);
					lp(i, x, v)
					{
						prevd[i - x] = prevd[i];
					}
					prevd[v - x] = '\0';
					// return;
				}
				if (f == 1)
				{
					printf("%s\n", prevd);
				}
				else
					printf("~%s\n", prevd);
			}
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
		strcpy(prevd, tempdir);
	}
	// handleonjobs();
}
