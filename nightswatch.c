#include "header.h"
void nightswatch(char *token)
{
	token = strtok (token + strlen (token) + 1, " \n");
	if (strcmp(token, "-n") != 0)
	{
		printf("Error Occured1\n");
		return;
	}
	token = strtok (token + strlen (token) + 1, " \n");
	int time = parsestringtoint(token);
	if (time == -1)
	{
		printf("Error Occured2\n");
		return;
	}
	token = strtok (token + strlen (token) + 1, " \n");
	if (strcmp(token, "interrupt\n") == 0 || strcmp(token, "interrupt") == 0)
	{
		lp(i, 0, 8)
		printf("   CPU%d   ", i);
		printf("\n");
		while (1)
		{
			int fd = open("/proc/interrupts", O_RDONLY);
			if (fd < 0)
			{
				perror("Unable to open file\n");
				return;
			}
			int cpucounts = 0;
			char buff[10000];
			read(fd, buff, 10000);
			char *ptr = strtok(buff, " ");
			while (strcmp(ptr, "1:") != 0)
			{
				ptr = strtok (ptr + strlen (ptr) + 1, " ");
				cpucounts++;
			}
			lp(i, 0, cpucounts - 1)
			{
				ptr = strtok (ptr + strlen (ptr) + 1, " ");
				printf("%7s   ", ptr);
			}
			printf("\n");
			sleep(time);
		}
	}
	else if (strcmp(token, "newborn\n") == 0 || strcmp(token, "newborn") == 0)
	{
		while (1)
		{
			int fd = open("/proc/loadavg", O_RDONLY);
			if (fd < 0)
			{
				perror("Unable to open file\n");
				return;
			}
			char buff[100];
			read(fd, buff, 100);
			char *ptr = strtok(buff, " \n");
			lp(i, 0, 4)
			{
				ptr = strtok (ptr + strlen (ptr) + 1, " \n");
			}
			printf("%s\n", ptr);
			sleep(time);
		}
	}
	// handleonjobs();
}