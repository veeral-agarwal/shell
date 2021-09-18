#include "headers.h"
void exitout()
{
	for(int i=0 ; i<onjobs ; i++)
	{
		if (!(fbjobs[i].status))
		{
			kill(fbjobs[i].pid, 9);
			// fbjobs[i].status = 0;
		}
	}
	exit(1);
}
