#include "../minishell.h"

static int env_list_len(t_env *env_list)
{
	int	i;

	i = 0;
	while (env_list)
	{
		i++;
		env_list = env_list->next;
	}
	return (i);
}

char **get_env_from_list(t_env *env_list)
{
	char	**env = NULL;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * env_list_len(env_list));
	while (env_list)
	{
		env[i] = ft_strdup(env_list->str);
		env_list = env_list->next;
		i++;
	}
	return (env);
}
