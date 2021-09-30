#include "minishell.h"

int	main()
{
	t_minish	minish;

	char *cmdline = ft_strjoin(getenv("USER"), "$>");
	while (1)
	{
		minish.line = readline(cmdline);
		add_history(minish.line);
		parser(&minish);
		if (!ft_strcmp(minish.line, "exit"))
			exit(0);
	}
	return (0);
}
