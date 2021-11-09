#include "../minishell.h"

static int	help(t_minish *minish)
{
	ft_pipes(minish, minish->env);
	return (2);
}

/**
**	@brief			distributes commands and builtins by function
**	@param	cmd		splited command
**	@return	int		1 if it is builtin, 0 if not
*/
int distribution(t_minish *minish, char **cmd, bool flag_is_pipe)
{
	(void)flag_is_pipe;
	(void)minish;
	if (flag_is_pipe == false && minish->cmdlst->next)
		return (help(minish));
	if (!ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "PWD"))
		g_status = ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "ENV"))
		g_status = ft_env(cmd, minish->env);
	else if (!ft_strcmp(cmd[0], "cd"))
		g_status = cd(cmd, minish->env);
	else if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "ECHO"))
		g_status = echo(cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		g_status = ft_export(cmd, minish->env, minish);
	else if (!ft_strcmp(cmd[0], "unset"))
		g_status = unset(cmd, minish->env, minish);
	else
		if (!ft_strcmp(cmd[0], "exit"))
		g_status = ft_exit(cmd);
	else
	{
		if (flag_is_pipe == false)
			ft_command(cmd, minish->env, minish);
		return (0);
	}
	return (1);
}
