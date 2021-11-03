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

# include <stdio.h>
int main()
{
	char	*str_path;
	char	*str_command;
	char	**path;
	int fd = open("file", O_RDWR);
	printf("! %d\n", fd);
	dup2(fd, 1);

	while (path[i])
	{
		str_path = ft_strjoin(path[i++], "/");
		str_command = ft_strjoin(str_path, cmd[0]);
		if (!access(str_command, F_OK))
		{
			execve(str_command, cmd, env);
		}
	}
}
