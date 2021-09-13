#include "headers.h"
void echo(char *token)
{
	while (1)
	{
		token = strtok (token + strlen (token) + 1, " ");
		if (token == NULL)
			break;
		printf("%s ", token);
	}
	printf("\b");
	handleonjobs();
}
