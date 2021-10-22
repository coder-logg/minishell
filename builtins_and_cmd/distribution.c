#include "../minishell.h"

/**
**	@brief	distributes commands and builtins by function
**	@param	env			environment
*/
void distribution(t_minish *minish, char **env)
{
	char	**splited;

	splited = ((t_cmd *) minish->cmdlst->content)->cmd_splited;
	if (ft_strchr(minish->line, '|') != 0)
		ft_pipes(minish, env);
	else if (ft_strcmp(splited[0], "pwd") == 0 ||
				ft_strcmp(splited[0], "PWD") == 0)
		ft_pwd(splited);
	else if (ft_strcmp(splited[0], "env") == 0 ||
				ft_strcmp(splited[0], "ENV") == 0)
		ft_env(splited, env);
	else if (!ft_strcmp(splited[0], "echo") && !ft_strcmp(splited[1], "-n"))
		echo_n(splited);
	else if (!ft_strcmp(splited[0], "cd"))
		cd(splited, env);
	else if (!ft_strcmp(splited[0], "exit"))
	{
		printf("exit\n");
		exit(0);
	}
	else
		ft_command(splited, env);
}
