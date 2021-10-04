#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	(void)argc;
	(void)argv; // это просто чтобы флаги не ругались
	char *cmdline = ft_strjoin(getenv("USER"), "$> ");
	while (1)
	{
		minish.line = readline(cmdline);
		add_history(minish.line);
		parser(&minish);
		if (is_all_spaces(minish.line) != 0)
		{
			minish.cmd = ft_split(minish.line, ' ');
			if (!minish.cmd)
				putstr_exit("ft_split: ");
			distribution(&minish, env);
		}
		if (!ft_strcmp(minish.line, "exit"))
			exit(0);
	}
	return (0);
}
