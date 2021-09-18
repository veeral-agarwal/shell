#include "headers.h"
void month(int x)
{
    if(x == 0)
    {
        printf(" Jan ");
    }
    else if(x == 1)
    {
        printf(" Feb ");
    }
    else if(x == 2)
    {
        printf(" Mar ");
    }
    else if(x == 3)
    {
        printf(" Apr ");
    }
    else if(x == 4)
    {
        printf(" May ");
    }
    else if(x == 5)
    {
        printf(" Jun ");
    }
    else if(x == 6)
    {
        printf(" Jul ");
    }
    else if(x == 7)
    {
        printf(" Aug ");
    }
    else if(x == 8)
    {
        printf(" Sep ");
    }
    else if(x == 9)
    {
        printf(" Oct ");
    }
    else if(x == 10)
    {
        printf(" Nov ");
    }
    else if(x == 11)
    {
        printf(" Dec ");
    }
}
void rwx(int x)
{
    if(x & 4)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if(x & 2)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if(x & 1)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
}
void ls(char *token)
{
	struct dirent *de;
	struct passwd *pd;
	struct group *gp;
	DIR *d = opendir(".");
	token = strtok (token + strlen (token) + 1, " \n");
	if (token == NULL || strcmp(token, ".") == 0 || strcmp(token, "-a") == 0)
	{
		int flag = 1;
		if (token != NULL )
		{
            if(strcmp(token, "-a") == 0)
            {
                flag = 0;
            }
		}
		while (1)
		{
			de = readdir(d);
			if (de == NULL)
            {
				break;
            }
			if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            {
                if(flag)
                {
                    continue;
                }
            }
			printf("%s  ", de->d_name);
		}
		printf("\n");
	}
	else if (strcmp(token, "..") == 0)
	{
		d = opendir("..");
		while (1)
		{
			de = readdir(d);
			if (de == NULL)
            {
				break;
            }
			if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            {
				continue;
            }
			printf("%s  ", de->d_name);
		}
		printf("\n");
	}
	else if (strcmp(token, "~") == 0)
	{
		d = opendir(root);
		while (1)
		{
			if ((!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")))
            {
				continue;
            }
			de = readdir(d);
			if (de == NULL)
            {
				break;
            }
			printf("%s  ", de->d_name);
		}
		printf("\n");
	}
	else if ((strcmp(token, "-l") == 0) || (strcmp(token, "-la") == 0) || (strcmp(token, "-al") == 0))
	{
		int flag = 0;
		if (strcmp(token, "-l") == 0)
		{
			// printf("wadwd\n");
			flag = 1;
		}
		while (1)
		{
			de = readdir(d);
			if (de == NULL)
            {
				break;
            }
			if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            {
                if(flag)
                {
                    continue;
                }
            }
			stat(de->d_name, &tp);
			switch (tp.st_mode & S_IFMT)
			{
			case S_IFBLK: printf("b"); break;
			case S_IFCHR: printf("c"); break;
			case S_IFDIR: printf("d"); break;
			case S_IFIFO: printf("p"); break;
			case S_IFLNK: printf("l"); break;
			case S_IFSOCK: printf("s"); break;
			default: printf("-"); break;
			}
			int x, oth, grp, user;
			x = tp.st_mode;
			struct tm *changetime;
			oth = x % 8;
			x /= 8;
			grp = x % 8;
			x /= 8;
			user = x % 8;
			rwx(user);
			rwx(grp);
			rwx(oth);
			printf(" %ld", tp.st_nlink);
			pd = getpwuid(tp.st_uid);
			gp = getgrgid(tp.st_gid);
			printf(" %10s", pd->pw_name);
			printf(" %10s", gp->gr_name );
			printf(" %12ld", tp.st_size);
			// printf(" %s", de->d_name);
			changetime = localtime(&tp.st_mtime);
			month(changetime->tm_mon);
			printf("%2d ", changetime->tm_mday);
			printf("%2d:", changetime->tm_hour);
			if ((changetime->tm_min / 10) > 0)
			{
				printf("%2d ", changetime->tm_min);
			}
			else
			{
				printf("0%1d ", changetime->tm_min);
			}
			printf("%s\n", de->d_name);
		}
	}
	else
	{
		char* direcs[100];
		int count = 0;
		while (token != NULL)
		{
			direcs[count] = token;
			// strcpy(direcs[count], token);
			count+=1;
			// printf("%s\n", direcs[count - 1]);
			token = strtok (token + strlen (token) + 1, " \n");
			if (token == NULL)
            {
				break;
            }
		}
		direcs[count] = NULL;
		// printf("%s\n", direcs[0]);
		if (count == 1)
		{
			// printf("%s\n", direcs[0]);
			DIR *d = opendir(direcs[0]);
			if (d != NULL)
			{
				// printf("dwad\n");
				while (1)
				{
					// printf("dwad\n");
					de = readdir(d);
					// printf("dwad\n");
					if (de == NULL)
                    {
						break;
                    }
					if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
                    {
						continue;
                    }
					printf("%s ", de->d_name);
				}
				printf("\n");
			}
			else
			{
				printf("Directory %s does not exists\n", direcs[0]);
			}
		}
		else
		{
            for(int i=0 ; i<count ; i++)
			{
				printf("%s:\n", direcs[i]);
				DIR *d = opendir(direcs[i]);
				if (d != NULL)
				{
					while (1)
					{
						de = readdir(d);
						if (de == NULL)
                        {
							break;
                        }
						if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
                        {
							continue;
                        }
						printf("%s ", de->d_name);
					}
					if (i != (count - 1))
                    {
						printf("\n\n");
                    }
					else
                    {
						printf("\n");
                    }
				}
				else
				{
					printf("Directory %s does not exits\n", direcs[i]);
				}
			}
		}
	}
	handleonjobs();
}