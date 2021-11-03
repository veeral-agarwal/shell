#include "header.h"
void jobs()
{
	int c = 0;
	// printf("fw\n");
	lp(i, 0, onjobs)
	{
		if (fbjobs[i].status == 1 || fbjobs[i].status == -1)
		{
			continue;
		}
		// printf("fw\n");
		char fs[100];
		sprintf(fs, "/proc/%d/status", fbjobs[i].pid);
		int fd = open(fs, O_RDONLY);
		if (fd < 0)
		{
			printf("[%d] Stopped %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
			c++;
			continue;
		}
		// printf("fw\n");
		char buf[100];
		read(fd, buf, 100);
		// printf("%s", buf);
		char * token;
		token = strtok(buf, " :\n\t\r");
		while (!(strcmp(token, "State") == 0))
		{
			// printf("fw\n");
			token = strtok(NULL, " :\n\t\r");
		}
		token = strtok(NULL, " :\n\t\r");
		if (!strcmp(token, "T"))
		{
			printf("[%d] Stopped %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
			c++;
		}
		else
		{
			printf("[%d] Running %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
			c++;
		}
	}
}