#include "header.h"
void sigtstpHandler (int sig_num)
{
	// printf("dwqad\n");
	if (onjobs == 0)
	{
		return;
	}
	kill(fbjobs[onjobs - 1].pid, 19);
	fbjobs[onjobs - 1].status = 0;
	// signal(SIGTSTP, sigtstpHandler);
	// printf("dwad\n");
	return;
}
void sigintHandler (int sig_num)
{
	if (onjobs == 0)
	{
		return;
	}
	kill(fbjobs[onjobs - 1].pid, 9);
}
void appendtofile()
{
	FILE *fp;
	fp = fopen(tempar, "w+");
	if (his_count <= 20)
	{
		lp(i, 0, his_count)
		{
			// printf("dwcx");
			fprintf(fp, "%s\n", hist[i]);
		}
	}
	else
	{
		int sp = his_count % 20;
		lp(i, sp, 20)
		{
			fprintf(fp, "%s\n", hist[i]);
		}
		sp = his_count % 20;
		lp(i, 0, sp)
		{
			fprintf(fp, "%s\n", hist[i]);
		}
	}
	fclose(fp);
}
void initialise_history()
{
	int fd = open(tempar, O_RDONLY);
	if (fd < 0)
	{
		perror("Unable to open file\n");
		return;
	}
	char buff[10000];
	read(fd, buff, 10000);
	char *ptr = strtok(buff, "\n");
	while (ptr != NULL)
	{
		strcpy(hist[his_count % 20], ptr);
		// hist[his_count % 20][strlen(ptr)] = '\0';
		his_count++;
		ptr = strtok(ptr + strlen(ptr) + 1, "\n");
	}
}
// void handleonjobs()
// {
// 	if (onjobs > 0 && fbjobs[onjobs - 1].status == 1)
// 	{
// 		printf("\n[%d]+ Stopped           %s\n", onjobs, fbjobs[onjobs - 1].job_name);
// 		fbjobs[onjobs - 1].status = 0;
// 	}
// }
void addhistory(char msg[], int n)
{
	printf("d\n");
	lp(i, 0, n - 1)
	hist[his_count][i] = msg[i];
	printf("d\n");
	hist[his_count][n] = '\0';
	his_count++;
}
int parsestringtoint(char *token)
{
	int x = 0;
	lp(i, 0, strlen(token))
	{
		if (token[i] < 48 && token[i] > 57)
			return -1;
		x = x * 10 + (token[i] - 48);
	}
	return x;
}
void substring()
{
	int f = 0;
	int x = strlen(root);
	lp(i, 0, x)
	{
		if (root[i] == cwd[i])
			continue;
		else
		{
			f = 1;
			break;
		}
	}
	if (f == 1)
	{
		return;
	}
	else
	{
		lp(i, strlen(root), strlen(cwd))
		{
			cwd[i - strlen(root)] = cwd[i];
		}
		cwd[strlen(cwd) - strlen(root)] = '\0';
		return;
	}
}
void checkred(char charr[])
{
	char * tk = NULL;
	tk = strtok(charr, " \n");
	while (tk != NULL)
	{
		// printf("%s\n", tk);
		if (!strcmp(tk, "<"))
		{
			tk = strtok(tk + strlen(tk) + 1, " \n");
			strcpy(infile, tk);
		}
		if (!strcmp(tk, ">") || !(strcmp(tk, ">>")))
		{
			tk = strtok(tk + strlen(tk) + 1, " \n");
			strcpy(outfile, tk);
		}
		tk = strtok(tk + strlen(tk) + 1, " \n");
	}
}
void command_handler(char buf[])
{
	// printf("%d\n", strlen(buf));
	// printf("dawdwdq\n");
	// printf("%s\n", buf);
	char* token = NULL;
	char argument[1024];
	lp(i, 0, 1024)
	{
		argument[i] = '\0';
	}
	char charr[1024];
	strcpy(charr, buf);
	int j = 2000;
	int k = strlen(buf);
	lp(i, 0, k)
	{
		if (buf[i] == '>' || buf[i] == '<')
		{
			j = i;
			break;
		}
	}
	int isappend = 0;
	lp(i, 0, k)
	{
		if (buf[i] == '>')
		{
			if (buf[i + 1] == '>')
			{
				isappend = 1;
			}
		}
	}
	lp(i, j, k)
	{
		buf[i] = '\0';
	}
	lp(i, 0, 102)
	{
		infile[i] = '\0';
		outfile[i] = '\0';
	}
	checkred(charr);
	int bin, bout, in, out;
	bin = dup(0);
	bout = dup(1);
	if (strlen(infile) > 0)
	{
		in = open(infile, O_RDONLY);
		if (in < 0)
		{
			printf("Input File Invalid\n");
			return;
		}
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (strlen(outfile) > 0)
	{
		if (isappend)
		{
			out = open(outfile, O_APPEND |  O_WRONLY , 0644);
			if (out < 0)
			{
				printf("Output File Invalid\n");
				return;
			}
		}
		else
		{
			printf("awd\n");
			out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	// printf("%s\n", token);
	token = strtok(buf, " \n");
	if ((strcmp(token, "cd\n") == 0) || (strcmp(token, "cd") == 0))
	{
		cd(token, argument);
	}
	else if (strcmp(token, "ls\n") == 0 || strcmp(token, "ls") == 0)
	{
		// printf("dwad\n");
		ls(token);
	}
	else if (strcmp(token, "echo\n") == 0 || strcmp(token, "echo") == 0)
	{
		printf("dwa\n");
		while (1)
		{
			token = strtok (token + strlen (token) + 1, " ");
			if (token == NULL)
				break;
			printf("%s ", token);
		}
	}
	else if (strcmp(token, "pwd\n") == 0 || strcmp(token, "pwd") == 0)
	{
		pwd();
	}
	else if (strcmp(token, "pinfo\n") == 0 || strcmp(token, "pinfo") == 0)
	{
		pinfo(token);
	}
	else if (strcmp(token, "nightswatch\n") == 0 || strcmp(token, "nightswatch") == 0)
	{
		nightswatch(token);
	}
	else if (strcmp(token, "history\n") == 0 || strcmp(token, "history") == 0)
	{
		history(token);
	}
	else if (strcmp(token, "quit\n") == 0 || strcmp(token, "quit") == 0)
	{
		exitout();
	}
	else if (strcmp(token, "setenv") == 0)
	{
		setEnv(token);
	}
	else if (strcmp(token, "unsetenv") == 0)
	{
		unSetEnv(token);
	}
	else if (strcmp(token, "jobs") == 0)
	{
		jobs();
	}
	else if (strcmp(token, "kjob") == 0)
	{
		kjob(token);
	}
	else if (strcmp(token, "fg") == 0)
	{
		fg(token);
	}
	else if (strcmp(token, "bg") == 0)
	{
		bg(token);
	}
	else if (strcmp(token, "overkill") == 0)
	{
		overkill();
	}
	else
	{
		// signal(SIGTSTP, sigtstpHandler);
		execute(token);
	}
	if (strlen(infile) > 0)
	{
		dup2(bin, 0);
		close(bin);
	}
	if (strlen(outfile) > 0)
	{
		dup2(bout, 1);
		close(bout);
	}
	// printf("|qqwdqdw\n");
	return;
}
int main(int argc, char* argv[])
{
	lp(i, 0, 1024)
	{
		prevd[i] = '\0';
	}
	signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
	nested_count = 0;
	his_count = 0;
	onjobs = 0;
	conjobs = 0;
	printf("\033[H\033[J");
	open("history.txt", O_CREAT, 0644);
	getcwd(root, 1024);
	strcpy(tempar, root);
	strcat(tempar, "/history.txt");
	initialise_history();
	// printf("%d\n", his_count );
	char * user = getenv("USER");
	char host[1000];
	gethostname(host, 1000);
	char buf[1024];
	lp(i, 0, 1024)
	{
		buf[i] = '\0';
	}
	while (1)
	{
		// signal(SIGTSTP, sigtstpHandler);
		char *line = NULL;
		char msg[1024];
		memset(msg, '\0', sizeof(msg));
		getcwd(cwd, 1024);
		substring();
		// if (onjobs != conjobs)
		// {
		// 	conjobs = onjobs;
		// 	if (fbjobs[onjobs - 1].status == 1)
		// 		printf("[%d] %d\n", onjobs, fbjobs[onjobs - 1].pid);
		// }
		printf("\033[1;34m");
		printf("<%s@%s:~%s> ", user, host, cwd);
		printf("\033[0m");
		int xt = fgets(msg, 1024, stdin);
		if (xt == 0)
		{
			printf("\n");
			exitout();
		}
		if (strlen(msg) == 1)
			continue;
		// addhistory(&msg, strlen(msg));
		lp(i, 0, strlen(msg) - 1)
		hist[his_count % 20][i] = msg[i];
		hist[his_count % 20][strlen(msg) - 1] = '\0';
		his_count++;
		appendtofile();
		// msg[strlen(msg)] = ' ';
		line = strtok (msg, ";\n");
		while (1)
		{
			strcpy(buf, line);
			// buf[strlen(buf)] = '\0';
			// strcpy(prev_comm, buf);
			// printf("%s\n", buf);
			execpipe(buf);
			line = strtok (line + strlen (line) + 1, ";\n");
			if (line == NULL)
				break;
		}
		lp(i, 0, 1024)
		{
			buf[i] = '\0';
		}
	}
}
