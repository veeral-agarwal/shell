#include "headers.h"
void cd(char *token, char argg[])
{
	token = strtok (token + strlen (token) + 1, " ");
	if (!token)
	{
		chdir(root);
		return;
	}
	int c = 0;
	while (token[c] == ' ')
	{
		c+=1;
	}
	for(int i=c ; i<strlen(token) - 1 ; i++)
	{
		argg[i - c] = token[i];
	}
	argg[strlen(token) - c - 1] = '\0';
	token = strtok (token + strlen (token) + 1, " ");
	if (!token)
	{
		int d;
		if (strcmp(argg, "~") == 0)
		{
			nested_count = 0;
			chdir(root);
		}
		else if (strcmp(argg, "..") == 0)
		{
			if (nested_count == 0)
			{
				chdir(argg);
			}
			else
			{
				nested_count-=1;
				chdir(argg);
			}
		}
		else
		{
			d = chdir(argg);
			if (d != -1)
			{
				nested_count+=1;
			}
			else
			{
				printf("Error: No such file or directory\n");
				return;
			}
		}
	}
	else
	{
		printf("Error: Two many arggs\n");
		return;
	}
	handleonjobs();
}
