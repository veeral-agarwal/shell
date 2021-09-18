#include<stdio.h>
#include<string.h>
#include <sys/utsname.h>
#include<pwd.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include <limits.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <langinfo.h>
#include <sys/wait.h>
#include <fcntl.h>
#define lp(i,a,b) for(int i=a;i<b;i++)

typedef struct {
	char job_name[1024];
	pid_t pid;
	int status;
} job;
job fbjobs[100];
int onjobs;
int conjobs;
char cwd[1024];
char root[1024];
char prev_comm[1024];
int nested_count;
struct stat tp;

void fg(char *);
void bg(char *);
void pinfo(char *);
void substring();
void exitout();
void handleonjobs();
void echo(char *);
void pwd();
void cd(char *token, char argument[]);
void ls(char *);