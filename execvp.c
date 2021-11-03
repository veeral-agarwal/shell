#include "header.h"

void schandler(int sig)
{
	// printf("dwadwad\n");
	pid_t pidn;
	int status;
	// pidn = wait(NULL);
	pidn = waitpid(-1, &status, WNOHANG);
	if (pidn > 0)
	{
		int j = -1;
		lp(i, 0, onjobs)
		{
			if (fbjobs[i].pid == pidn)
			{
				j = i;
				fbjobs[i].status = 0;
				break;
			}
		}
		if (WEXITSTATUS(status) == 0 && WIFEXITED(status) && (j != -1))
		{
			printf("%s with pid %d exited normally\n", fbjobs[j].job_name, fbjobs[j].pid);
			fbjobs[j].status = -1;
		}
		else if (j != -1)
		{
			printf("%s with pid %d failed to exit normally\n", fbjobs[j].job_name, fbjobs[j].pid);
			fbjobs[j].status = -1;
		}
	}
	// else
	// {
	// 	printf("Process terminated\n");
	// }
}
void execute(char *token)
{
	// printf("awd\n");
	pid_t pid;
	int status;
	char* arg[100];
	int count = 0;
	while (token != NULL)
	{
		arg[count] = token;
		count++;
		token = strtok (token + strlen (token) + 1, " \n");
	}
	arg[count] = NULL;
	int isbg = 0;
	if (strcmp(arg[count - 1], "&") == 0)
	{
		// printf("312\n");
		isbg = 1;
		signal(SIGCHLD, schandler);
	}
	else
	{
		// signal(SIGTSTP, sigtstpHandler);
	}
	pid = fork();
	if (pid == 0)
	{
		// printf("wdqwd\n");
		if (strcmp(arg[count - 1], "&") == 0)
		{
			setpgid(0, 0);
			// printf("wdqwd\n");
			arg[count - 1] = NULL;
			// close(STDERR_FILENO);
		}
		int exec = execvp(arg[0], arg);
		if (exec < 0)
		{
			printf("Error! Execution failed\n");
		}
		// printf("asd\n");
	}
	else if (pid > 0)
	{
		// sleep(10);
		if (!isbg)
		{
			fbjobs[onjobs].pid = pid;
			strcpy(fbjobs[onjobs].job_name, arg[0]);
			fbjobs[onjobs].status = 1;
			onjobs++;
			// fbjobs[onjobs].status = 0;
			waitpid(pid, &status, WUNTRACED);
			if (WIFSTOPPED(status))
			{
				// printf("wad\n");
				fbjobs[onjobs - 1].status = 0;
			}
		}
		if (isbg)
		{
			fbjobs[onjobs].pid = pid;
			strcpy(fbjobs[onjobs].job_name, arg[0]);
			fbjobs[onjobs].status = 0;
			onjobs++;
			printf("[%d]    %s\n", onjobs, fbjobs[onjobs - 1].job_name);
		}
	}
}
