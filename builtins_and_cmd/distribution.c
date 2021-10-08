#include "../minishell.h"

/*
**	@brief	distributes commands and builtins by function
**	@param	env			environment
*/
void distribution(t_minish *minish, char **env)
{
	if (ft_strcmp(minish->cmd[0], "pwd") == 0 ||
		ft_strcmp(minish->cmd[0], "PWD") == 0)
		ft_pwd(minish);
	else if (ft_strcmp(minish->cmd[0], "env") == 0 ||
		ft_strcmp(minish->cmd[0], "ENV") == 0)
		ft_env(minish, env);
	else
		run_cmd(minish->line, env);
}
