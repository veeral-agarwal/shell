#include "headers.h"
void pwd()
{
	getcwd(cwd, 100);
	printf("%s", cwd);
	printf("\n");
	handleonjobs();
}