# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

int gl;

int foo()
{
	int pid;
	int a;
	pid = fork();
	a = 0;
	if (pid == 0)
	{
		a = 5;
		printf("daut a=%d\n", a);
		// gl = 9;
		// printf("daut %d\n", gl);
	}
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		printf("parent after fork %d\n", a);
	}
	return (a);
}

// int main()
// {
// 	printf("parent %d\n", gl);
// 	gl = 3;
// 	printf("parent2 %d\n", gl);
// 	gl = foo();
// 	printf("parent finish %d\n", gl);
// }
