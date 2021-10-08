#include "../minishell.h"

bool is_env_chr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

/**
 * @brief return environment variable's value
 * @param str should point to symbol '$'
 * @param env_name buffer to environment variable's name
 * @return environment variable's value or <b><i>NULL</i></b> if doesn't
 * exist or if <i><b>str = NULL</b></i>
 */
char *get_env(char *str, char *env_name)
{
	unsigned int	j;

	if (*str == '$')
	{
		ft_bzero(env_name, 200);
		j = 0;
		env_name[j++] = *str;
		if (ft_isdigit(*(++str)))
			return (NULL);
		while (*str && *str != '\"' && is_env_chr(*str))
			env_name[j++] = (*str)++;
		return (getenv(env_name));
	}
	return (NULL);
}

void	read_env(char **str, int pos)
{
	char	*env_val;
	char	env_name[200];

	env_val = get_env(*str + pos, env_name);
	if (env_val)
	{
		set_free((void **)str,replace_subst(*str + pos, env_name, env_val));
		free(env_val);
	}
}

int parse_quotes(char **str, int i)
{
	char	quot;

	if ((*str)[i] != '\"' && (*str)[i] != '\'')
		return (i);
	quot = (*str)[i];
	set_free((void **)str,replace_subst(*str + i, "\"", ""));
	while ((*str)[i++])
	{
		if ((*str)[i] == '$' && quot == '\"')
			read_env(str, i);
		if ((*str)[i] == quot)
		{
			set_free((void **)str,replace_subst(*str + i, "\"", ""));
			break ;
		}
	}
	return (i);
}

void parser(t_minish *minish)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_strdup(minish->line);
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i = parse_quotes(&line, i);
		}
		if (line[i] == '$')
			read_env(&line, i);
		i++;
	}
	char *first_space = ft_strchr(minish->line, ' ');
	if (first_space)
	{
		minish->cmd[0] = ft_substr(minish->line, 0, first_space - minish->line);
		line = ft_strdup(first_space);
	}
	else
		line = ft_strdup(minish->line);
}
