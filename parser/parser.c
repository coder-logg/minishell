# include "../minishell.h"

typedef	struct s_parse_quotes
{
	char			*res;
	char			*quot;
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
 * @fn char	*read_env(char **str, char *env_name)
 * @brief return environment variable's value
 *
 * @param str should point to symbol '$'
 * @param env_name buffer to environment variable's name
 *
 * @return environment variable's value or NULL if doesn't exist or if
 * 			\code str = NULL \endcode
 */
char *read_env(char **str, char *env_name)
{
	unsigned int	j;

	if (**str == '$')
	{
		ft_bzero(env_name, 200);
		j = 0;
		if (ft_isdigit(**str))
			return (NULL);
		while (*(*str)++)
		{
			if (is_env_chr(**str))
				env_name[j++] = **str;
//			else if (**str == quot)
//			{
//				(*str)--;
//				return (NULL);
//			}
			else
				break ;
		}
		return (getenv(env_name));
	}
	return (NULL);
}

char	*parse_quotes(char **str)
{
	unsigned int	i;
	t_parse_quotes	pars_qoutes;
	if (**str != '\"' && **str != '\'')
		return (NULL);
	pars_qoutes.quot = (*str);
	pars_qoutes.second_quot = ft_strchr(*str + 1, *pars_qoutes.quot);
//	todo if quotes aren't closed make heredoc
	if (pars_qoutes.second_quot == NULL)
		pars_qoutes.second_quot = pars_qoutes.quot + ft_strlen(pars_qoutes.quot + 1);
	pars_qoutes.res = ft_calloc(pars_qoutes.second_quot - pars_qoutes.quot, sizeof(char));
	if (!pars_qoutes.res)
		exit(10);
	i = 0;
	while (*(*str)++)
	{
		if (**str == *pars_qoutes.quot)
			break ;
		if (**str == '$' && *pars_qoutes.quot == '\"')
		{
			pars_qoutes.env_val = read_env(str, pars_qoutes.env_name);
			if (!pars_qoutes.env_val)
			{
				char *new_res = ft_calloc(
						pars_qoutes.second_quot - pars_qoutes.quot - 1 -
						ft_strlen(pars_qoutes.env_name) + ft_strlen(pars_qoutes.env_val), sizeof(char));
				ft_strcpy(new_res, pars_qoutes.res);
				free(pars_qoutes.res);
				pars_qoutes.res = new_res;
				ft_strcpy(pars_qoutes.res + i, pars_qoutes.env_val);
				i += ft_strlen(pars_qoutes.env_val);
			}
		}
		pars_qoutes.res[i++] = **str;
	}
	return (pars_qoutes.res);
}


void parser(t_minish *minish)
{
	char	*str;

	str = ft_strdup(minish->line);
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			printf("%s\n", parse_quotes(&str));
			str++;
			continue ;
		}
		str++;
	}
}
