#include "minishell.h"

int		g_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	(void)argc;
	(void)argv;
	// rl_outstream = stderr;
	char *cmdline = ft_strjoin(getenv("USER"), "$>");
	minish.cmdlst = NULL;
	minish.env = copystr_array(env);
	while (1)
	{
		minish.line = readline(cmdline);
		add_history(minish.line);
		parser(&minish);
		if (minish.line[0])
			distribution(&minish, minish.env);
		ft_lstclear(&minish.cmdlst, &destroy_node);
		free(minish.line);
		minish.line = NULL;
	}
	return (0);
}
