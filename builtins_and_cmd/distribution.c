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
		g_status = ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "ENV"))
		g_status = ft_env(cmd, minish->env);
	else if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd, env);
	else if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "ECHO"))
		g_status = echo(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, minish->env);
	else if (!ft_strcmp(cmd[0], "exit"))
		g_status = ft_exit(cmd);
	// else if ...
	else
	{
		if (minish != NULL)
			ft_command(cmd, minish->env);
		return (0);
	}
	return (1);
}
