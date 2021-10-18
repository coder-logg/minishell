#include "../minishell.h"

/**
**	@brief	distributes commands and builtins by function
**	@param	env			environment
*/
void distribution(char **splited, char **env)
{
	
	if (ft_strcmp(splited[0], "pwd") == 0 ||
		ft_strcmp(splited[0], "PWD") == 0)
		ft_pwd(splited);
	else if (ft_strcmp(splited[0], "env") == 0 ||
		ft_strcmp(splited[0], "ENV") == 0)
		ft_env(splited, env);
	else if (!ft_strcmp(splited[0], "echo") && ft_strcmp(splited[1], "-n"))
		echo_n(splited);
	else
		run_cmd(splited, env);
}
