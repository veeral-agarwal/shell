#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#define lp(i,a,b) for(int i=a;i<b;i++)
#define rlp(i,a,b) for(int i=a;i>=b;i--)
#define ll long long int
typedef struct {
	char job_name[1024];
	pid_t pid;
	int status;
} job;
int nested_count;
int xsd;
char root[1024];
char prevd[1024];
char cwd[1024];
char hist[20][1024];
job fbjobs[100];
int his_count;
struct stat tp;
int onjobs;
int conjobs;
char tempar[1024];
// char prev_comm[1024];
char infile[102];
char outfile[102];
void month(int);
void schandler(int);
void appendtofile();
void initialise_history();
void handleonjobs();
void addhistory(char [], int);
void printhistory(int);
void rwx(int);
int parsestringtoint(char *);
void substring();
void cd(char *, char []);
void ls(char *);
void echo(char *);
void pwd();
void pinfo(char *);
void nightswatch(char *);
void history(char *);
void exitout();
void execute(char *);
void execpipe(char []);
void command_handler(char []);
void setEnv(char *);
void unSetEnv(char *);
void jobs();
void kjob();
void fg(char *);
void bg(char *);
void overkill();