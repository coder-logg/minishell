#include "../minishell.h"

/**
**	@brief	distributes commands and builtins by function
**	@param	env			environment
*/
void distribution(t_minish *minish, char **env)
{
	if (ft_strchr(minish->line, '|') != 0)
		ft_pipes(minish, env);
	else if (ft_strcmp(((t_cmd *)minish->cmdlst->content)->cmd_splited[0], "pwd") == 0 ||
		ft_strcmp( ((t_cmd *)minish->cmdlst->content)->cmd_splited[0], "PWD") == 0)
		ft_pwd(((t_cmd *)minish->cmdlst->content)->cmd_splited);
	else if (ft_strcmp(((t_cmd *)minish->cmdlst->content)->cmd_splited[0], "env") == 0 ||
		ft_strcmp(((t_cmd *)minish->cmdlst->content)->cmd_splited[0], "ENV") == 0)
		ft_env(((t_cmd *)minish->cmdlst->content)->cmd_splited, env);
	else
		ft_command(((t_cmd *)minish->cmdlst->content)->cmd_splited, env);
}
