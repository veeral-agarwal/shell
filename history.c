#include "header.h"
void printhistory(int n)
{
	if (his_count <= 20)
	{
		int x = (his_count - n) >= 0 ? his_count - n : 0;
		lp(i, x, his_count)
		{
			printf("%s\n", hist[i]);
		}
	}
	else
	{
		int setpointer = (his_count - n) % 20;
		if (setpointer >= (his_count % 20))
		{
			lp(i, setpointer, 20)
			printf("%s\n", hist[i]);
			lp(i, 0, his_count % 20)
			printf("%s\n", hist[i]);
		}
		else
		{
			lp(i, setpointer, his_count)
			printf("%s\n", hist[i]);
		}
	}
}
void history(char *token)
{
	token = strtok(token + strlen(token) + 1, " \n");
	if (token == NULL)
		printhistory(10);
	else
	{
		int x = parsestringtoint(token);
		printhistory(x);
	}
	// handleonjobs();
}