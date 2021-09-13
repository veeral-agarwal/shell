#include "headers.h"

void substring()
{
	lp(i, strlen(root), strlen(cwd))
	{
		cwd[i - strlen(root)] = cwd[i];
	}
	cwd[strlen(cwd) - strlen(root)] = '\0';
	return;
}

void command_handler(char buf[])
{
    nested_count = 0;
    char* token = NULL;
    char argument[1024];
    token = strtok(buf, " \n");
    if (strcmp(token, "echo\n") == 0 || strcmp(token, "echo") == 0)
	{
		echo(token);
	}
    else if (strcmp(token, "pwd\n") == 0 || strcmp(token, "pwd") == 0)
	{
		pwd();
	}
    else if ((strcmp(token, "cd\n") == 0) || (strcmp(token, "cd") == 0))
	{
		cd(token, argument);
	}
    
	return;
}

void handleonjobs()
{
	if (onjobs > 0 && fbjobs[onjobs - 1].status == 1)
	{
		printf("\n[%d]+ Stopped           %s\n", onjobs, fbjobs[onjobs - 1].job_name);
		fbjobs[onjobs - 1].status = 0;
	}
}




int main(int argc, char* argv[])
{
    onjobs = 0;
	conjobs = 0;
    printf("\033[H\033[J");
    char * user = getenv("USER");
    char host[1024];
    gethostname(host, 1024);
    getcwd(root, 1024);
    char buf[1024];
    while(1)
    {
        char * line = NULL;
        char msg[1024];
        memset(msg, '\0', sizeof(msg));
        getcwd(cwd, 1024);
        substring();
        printf("\033[1;34m");
		printf("<%s@%s:~%s> ", user, host, cwd);
		printf("\033[0m");
        fgets(msg, 1024, stdin);
		if (strlen(msg) == 1)
			continue;
        msg[strlen(msg)] = ' ';
		line = strtok (msg, ";");
        while(1)
        {
            strcpy(buf, line);
			buf[strlen(buf)] = '\0';
			strcpy(prev_comm, buf);
			command_handler(buf);
			line = strtok (line + strlen (line) + 1, ";");
			if (line == NULL)
				break;
        }
    }

}