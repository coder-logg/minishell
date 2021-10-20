#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	(void)argc;
	(void)argv;
	char *cmdline = ft_strjoin(getenv("USER"), "$>");
	minish.cmdlst = NULL;
	while (1)
	{
		minish.line = readline(cmdline);
		add_history(minish.line);
		parser(&minish);
		distribution(&minish, env);
		ft_lstclear(&minish.cmdlst, &destroy_node);
		free(minish.line);
		minish.line = NULL;
	}
	return (0);
}
