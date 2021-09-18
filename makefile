shell: main.c
	gcc -ggdb -o shell main.c pwd.c echo.c exit.c cd.c ls.c pinfo.c fg.c bg.c