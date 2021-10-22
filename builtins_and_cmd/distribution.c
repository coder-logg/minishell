#include "../minishell.h"

/**
**	@brief			distributes commands and builtins by function
**	@param	cmd		splited command
**	@param	env		environment
**	@return	int		1 if it is builtin, 0 if not
*/
int	distribution(t_minish *minish, char **cmd, char **env)
{
	if (minish != NULL && ft_strchr(minish->line, '|'))
	{
		ft_pipes(minish, env);
		return (2);
	}
	if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "PWD"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "ENV"))
		ft_env(cmd, env);
	// else if ...
	else
	{
		if (minish != NULL)
			ft_command(cmd, env);
		return (0);
	}
	return (1);
}
