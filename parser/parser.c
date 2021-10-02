# include "../minishell.h"

typedef	struct s_parse_quotes
{
	char			*res;
	char			*first_quot;
	char			*second_quot;
	char			*env_val;
	char			env_name[200];
}				t_parse_quotes;

bool is_env_chr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

/**
 * @brief return environment variable's value
 *
 * @param str should point to symbol '$'
 * @param env_name buffer to environment variable's name
 *
 * @return environment variable's value or <b><i>NULL</i></b> if doesn't
 * exist or if <i><b>str = NULL</b></i>
 */
char *read_env(char **str, char *env_name)
{
	unsigned int	j;

	if (**str == '$')
	{
		ft_bzero(env_name, 200);
		j = 0;
		if (ft_isdigit(*(*str)++))
			return (NULL);
		while (**str && **str != '\"' && is_env_chr(**str))
			env_name[j++] = *(*str)++;
		return (getenv(env_name));
	}
	return (NULL);
}

void replace_env_name_with_val(unsigned int *i, t_parse_quotes *pars_qoutes)
{
	char *new_res;
	unsigned long new_str_len;

	new_str_len = pars_qoutes->second_quot - pars_qoutes->first_quot - 1 -
			ft_strlen(pars_qoutes->env_name) + ft_strlen(pars_qoutes->env_val);
	new_res = ft_calloc(new_str_len, sizeof(char));
	if (!new_res)
		exit(10);
	ft_strcpy(new_res, pars_qoutes->res);
	free(pars_qoutes->res);
	pars_qoutes->res = new_res;
	ft_strcpy(pars_qoutes->res + (*i), pars_qoutes->env_val);
	(*i) += ft_strlen(pars_qoutes->env_val);
}

char	*parse_quotes(char **str)
{
	unsigned int	i;
	t_parse_quotes	pars_qoutes;

	if (**str != '\"' && **str != '\'')
		return (NULL);
	pars_qoutes.first_quot = (*str);
	pars_qoutes.second_quot = ft_strchr(*str + 1, *pars_qoutes.first_quot);
//	todo if quotes aren't closed make heredoc
	if (pars_qoutes.second_quot == NULL)
		pars_qoutes.second_quot = pars_qoutes.first_quot + ft_strlen(pars_qoutes.first_quot + 1);
	pars_qoutes.res = ft_calloc(pars_qoutes.second_quot - pars_qoutes.first_quot, sizeof(char));
	if (!pars_qoutes.res)
		exit(10);
	i = 0;
	while (*(*str)++)
	{
		if (**str == '$' && *pars_qoutes.first_quot == '\"')
		{
			pars_qoutes.env_val = read_env(str, pars_qoutes.env_name);
			if (pars_qoutes.env_val)
				replace_env_name_with_val(&i, &pars_qoutes);
		}
		if (**str == *pars_qoutes.first_quot)
			break ;
		pars_qoutes.res[i++] = **str;
	}
	return (pars_qoutes.res);
}

void parser(t_minish *minish)
{
	char	*line;
	int		i;
	char	*str_in_quots;

	i = 0;
//	char *first_space = ft_strchr(minish->line, ' ');
//	if (!first_space)
//	{
//		minish->cmd[0] = ft_substr(minish->line, 0, first_space - minish->line);
//		line = ft_strdup(first_space);
//	}
//	else
	line = ft_strdup(minish->line);
	while (line[i])
	{
		if (*line == '\"' || *line == '\'')
		{
			char *tmp = line;
			char *str_in_quotes = parse_quotes(&line);
			if (str_in_quotes != NULL)
			{
				str_in_quots = ft_strjoin(tmp, str_in_quotes);
				free(str_in_quotes);
				free();
			}
			if(!str_in_quots)
				exit(-1);
		}
		i++;
	}
}
