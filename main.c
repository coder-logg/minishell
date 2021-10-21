#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	(void)argc;
	(void)argv;
	// (void)env;
	char *cmdline = ft_strjoin(getenv("USER"), "$>");
	minish.cmdlst = NULL;
	minish.env = copystr_array(env);
	while (1)
	{
		minish.line = readline(cmdline);
		add_history(minish.line);
		parser(&minish);
		if (minish.line[0])
			minish.status = distribution(
					((t_cmd *)minish.cmdlst->content)->cmd_splited, minish.env);
		ft_lstclear(&minish.cmdlst, &destroy_node);
		free(minish.line);
	}
	return (0);
}
