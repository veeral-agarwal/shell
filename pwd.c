#include "header.h"
void pwd()
{
	getcwd(cwd, 100);
	printf("%s\n", cwd);
	// handleonjobs();
}