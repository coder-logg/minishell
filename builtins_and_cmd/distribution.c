#include "../minishell.h"

/**
**	@brief			distributes commands and builtins by function
**	@param	cmd		splited command
**	@param	env		environment
**	@return	int		1 if it is builtin, 0 if not
*/
int	distribution(t_minish *minish, char **cmd, char **env, bool flag_is_pipe)
{
	if (flag_is_pipe == false && minish->cmdlst->next)
	{
		ft_pipes(minish, env);
		return (2);
	}
	if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "PWD"))
		g_status = ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "ENV"))
		g_status = ft_env(cmd, minish->env);
	else if (!ft_strcmp(cmd[0], "cd"))
		g_status = cd(cmd, env);
	else if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "ECHO"))
		g_status = echo(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, minish->env);
	else if (!ft_strcmp(cmd[0], "exit"))
		g_status = ft_exit(cmd);
	// else if ...
	else
	{
		if (flag_is_pipe == false)
			ft_command(cmd, minish->env);
		return (0);
	}
	return (1);
}
