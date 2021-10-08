#include "../minishell.h"
#include "parser.h"

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
		j = 0;
		if (ft_isdigit(*(++str)))
			return (NULL);
		while (*str && *str != '\"' && is_env_chr(*str))
			env_name[j++] = *(str++);
		return (getenv(env_name));
	}
	return (NULL);
}

int	read_env(char **str, int pos)
{
	char	*env_val;
	char	env_name[200];

	ft_bzero(env_name, 200);
	env_name[0] = '$';
	env_val = get_env(*str + pos, env_name + 1);
	if (env_val)
	{
		set_free((void **)str, replace_subst(*str, env_name, env_val, 0));
	}
	return (pos + ft_strlen(env_val));
}

int parse_quotes(char **str, int i)
{
	char	quot;

	if ((*str)[i] != '\"' && (*str)[i] != '\'')
		return (i);
	quot = (*str)[i];
	set_free((void **)str, replace_subst(*str, "\"", "", 0));
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && quot == '\"')
		{
			i = read_env(str, i);
			continue ;
		}
		if ((*str)[i] == quot)
		{
			char ch[2];
			ch[0] = quot;
			ch[1] = '\0';
			set_free((void **)str, replace_subst(*str, ch, "", 0));
			break ;
		}
		i++;
	}
	return (i);
}

/**
 * counts number of occurrences of character <b><i>ch</i></b>
 * in string <b><i>str</i></b>
 */
int count_symbol_occur(char *str, char ch)
{
	int counter;

	counter = 0;
	while (*(str))
	{
		if (*str++ == ch)
			counter++;
	}
	return(counter);
}

void parser(t_minish *minish)
{
	char	*line;
	int		i;
	int		prev_spc;
	int		words_cntr;

	i = 0;
	words_cntr = 0;
	prev_spc = 0;
	line = ft_strdup(minish->line);
	minish->cmd = check_malloc(
			ft_calloc(count_symbol_occur(line, ' ') + 1, sizeof(char *)));
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i = parse_quotes(&line, i);
			continue ;
		}
		if (line[i] == '$')
		{
			i = read_env(&line, i);
			continue ;
		}
		if (line[i] == '\t')
		{
			char ch[2];
			ch[0] = '\t';
			ch[1] = '\0';
			set_free((void **)&line,replace_subst(line, ch, " ", i));
		}
		if (line[i] == ' ')
		{
			set_free((void **)&line, collapse_symbols(line, i, ' '));
			minish->cmd[words_cntr++] = check_malloc(
					ft_substr(line + prev_spc, 0, i - prev_spc));
			prev_spc = i + 1;
		}
		i++;
	}
	minish->line = line;
	minish->cmd[words_cntr++] = check_malloc(
			ft_substr(line + prev_spc, 0, i - prev_spc));

//	i = 0;
//
//	while (i < words_cntr)
//	{
//		printf("%s\n", minish->cmd[i++]);
//	}
}
