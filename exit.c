#include "headers.h"
void exitout()
{
	lp(i, 0, onjobs)
	{
		if (fbjobs[i].status == 0)
		{
			kill(fbjobs[i].pid, 9);
			// fbjobs[i].status = 0;
		}
	}
	exit(1);
}