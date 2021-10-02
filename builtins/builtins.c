#include "../minishell.h"

static void ft_pwd(t_minish *minish)
{
	char *str;
	int len;

	len = 0;
	while (minish->cmd[len])
		len++;
	if (len > 1)
	{
		error_builtin(minish->cmd[0]);
		return ;
	}
	str = getenv("PWD");
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

static void ft_env(t_minish *minish, char **env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (minish->cmd[len])
		len++;
	if (len > 1)
	{
		error_builtin(minish->cmd[0]);
		return ;
	}
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}

void check(t_minish *minish, char **env)
{
	if (ft_strcmp(minish->cmd[0], "pwd") == 0 ||
		ft_strcmp(minish->cmd[0], "PWD") == 0)
		ft_pwd(minish);
	else if (ft_strcmp(minish->cmd[0], "env") == 0 ||
		ft_strcmp(minish->cmd[0], "ENV") == 0)
		ft_env(minish, env);
	else
		cmd_not_found(minish->cmd[0]);
}
