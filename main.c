#include "minishell.h"

int		g_status;

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	(void)argc;
	(void)argv;
	// rl_outstream = stderr;
	minish.cmdlst = NULL;
	minish.env = copystr_array(env);
	while (1)
	{
		minish.line = readline("minishell$> ");
		if (minish.line[0])
		{
			add_history(minish.line);
		}
		else
		{
			free(minish.line);
			minish.line = NULL;
			continue;
		}
		parser(&minish);
		if (minish.line[0])
			distribution(&minish, ((t_cmd *)minish.cmdlst->content)->cmd_splited, minish.env, false);
		ft_lstclear(&minish.cmdlst, &destroy_node);
		free(minish.line);
		minish.line = NULL;
	}
	return (0);
}
