#include "header.h"
void overkill()
{
	lp(i, 0, onjobs)
	{
		if (fbjobs[i].status == 0)
		{
			fbjobs[i].job_name[0] = '\0';
			kill(fbjobs[i].pid, 9);
		}
	}
	onjobs = 0;
}