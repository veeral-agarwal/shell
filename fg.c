#include "header.h"
void fg(char *token)
{
	int arg;
	token = strtok(token + strlen(token) + 1, " \n");
	if (token == NULL)
	{
		perror("Less number of arguments passed\n");
		return;
	}
	sscanf(token, "%d", &arg);
	token = strtok(token + strlen(token) + 1, " \n");
	if (token != NULL)
	{
		perror("More number of arguments entered than required");
		return;
	}
	if (arg > onjobs)
	{
		perror("Enter valid job number\n");
		return;
	}
	int c = 0;
	int f = 0;
	pid_t pid;
	int j = 0;
	lp(i, 0, onjobs)
	{
		if (fbjobs[i].status == 0)
			c++;
		if (c == arg)
		{
			pid = fbjobs[i].pid;
			f = 1;
			j = i;
			break;
		}
	}
	if (f == 0)
	{
		perror("Could not find any valid Process\n");
		return;
	}
	int status;
	pid_t shellpid = getpid();
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	tcsetpgrp(0, getpgid(fbjobs[arg - 1].pid));
	kill(fbjobs[arg - 1].pid, SIGCONT);
	waitpid(fbjobs[arg - 1].pid, &status, WUNTRACED);
	tcsetpgrp(0, shellpid);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	fbjobs[j].status = 1;
	if (WIFSTOPPED(status))
	{
		fbjobs[j].status = 0;
	}
}