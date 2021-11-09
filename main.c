#include "minishell.h"

int		g_status;

void	ctrl_d()
{
	write(2, "exit\n", 5);	
	exit(g_status);
}

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	minish.cmdlst = NULL;
	minish.env = copystr_array(env);
	change_shell_lvl(&minish);
	ctrl_ign();
	while (1)
	{
		main_signals();
		minish.line = readline("\x1b[32mminishell$>\x1b[0m ");
		if (minish.line == NULL)
			ctrl_d();
		if (minish.line[0])
			add_history(minish.line);
		else
		{
			free(minish.line);
			minish.line = NULL;
			continue ;
		}

		if (!parser(&minish) && minish.line[0] && ((t_cmd *)minish.cmdlst->content)->cmd_splited)
		{
			distribution(&minish,
						 ((t_cmd *) minish.cmdlst->content)->cmd_splited, false);
		}
		ft_lstclear(&minish.cmdlst, &destroy_node);
		free(minish.line);
		minish.line = NULL;
	}
	return (0);
}
