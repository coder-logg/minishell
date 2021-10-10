#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	argc = 0;
	(void)argv; // это просто чтобы флаги не ругались
	char *cmdline = ft_strjoin(getenv("USER"), "$>");
	while (1)
	{
		minish.line = readline(cmdline);
		add_history(minish.line);
		parser(&minish);
		distribution(&minish, env);
	}
	return (0);
}
