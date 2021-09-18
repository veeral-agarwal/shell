#include "headers.h"
void pinfo(char *token)
{
	token = strtok (token + strlen (token) + 1, " \n");
	char prp[100] = "/proc/";
	char pd[20];
	if (token == NULL)
	{
		int pid = getpid();
		sprintf(pd, "%d", pid);
		strcat(prp, pd);
	}
	else
	{
		strcat(prp, token);
	}
	strcat(prp, "/stat");
	char buff[10000];
	int fd = open(prp, O_RDONLY);
	if (fd < 0)
	{
		perror("Error....Unable to open file!!\n");
		// exit(0);
	}
	char* arr[1000];
	read(fd, buff, 10000);
	char *ptr = strtok(buff, " ");
	int nc = 0;
	while (ptr != NULL)
	{
		arr[nc] = ptr;
		nc++;
		ptr = strtok (ptr + strlen (ptr) + 1, " ");
	}
	printf("pid -- %s\n", token == NULL ? pd : token );
	printf("Process Status -- %s\n", arr[2]);
	printf("memory -- %s    {Virtual Memory}\n", arr[22]);
	sprintf(prp, "/proc/%s/exe", token == NULL ? pd : token);
	char pathexe[1000];
	readlink(prp, pathexe, 1000);
	// pathexe[strlen(pathexe)] = '\0';
	printf("Executable Path -- %s\n", pathexe);
	lp(i, 0, 1000)
	pathexe[i] = '\0';
	handleonjobs();
}