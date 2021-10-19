#include "../minishell.h"

void	cd(char **cmd_splited)
{
	char	*path;

	if (arr_len(cmd_splited) == 1)
		path = getenv("HOME");
	else
		path = cmd_splited[1];
	chdir(path);
}