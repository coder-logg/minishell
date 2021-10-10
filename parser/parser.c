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
 * @param env_name_dst buffer to environment variable's name
 * @return environment variable's value or <b><i>NULL</i></b> if doesn't
 * exist or if <i><b>str = NULL</b></i>
 */
char *get_env(char *str, char *env_name_dst)
{
	unsigned int	j;

	if (*str == '$')
	{
		j = 0;
		if (ft_isdigit(*(++str)))
			return (NULL);
		while (*str && *str != '\"' && is_env_chr(*str))
			env_name_dst[j++] = *(str++);
		return (getenv(env_name_dst));
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

void if_tab_or_space(t_minish *minish, int i, char **line, char if_end)
{
	static int	prev_spc = 0;
	static int	words_cntr = 0;
	char		ch_str[2];

	ch_str[1] = '\0';
	if (i == 0)
		words_cntr = 0;
	(void)if_end;
	if ((*line)[i] == '\t')
	{
		ch_str[0] = '\t';
		set_free((void **)line, replace_subst(*line, ch_str, " ", i));
	}
	if ((*line)[i] == ' ' || !(*line)[i])
	{
		set_free((void **) line, shrink_chs_one(*line, i, ' '));
		minish->cmd[words_cntr++] = check_malloc(
				ft_substr(*line + prev_spc, 0, i - prev_spc));
		prev_spc = i + 1;
	}
//	if (if_end == 'e')
//		minish->cmd[words_cntr++] = check_malloc(
//				ft_substr(*line + prev_spc, 0, i - prev_spc));
}

void parser(t_minish *minish)
{
	char	*line;
	int		i;
	char	ch_str[2];

	i = 0;
	ch_str[1] = '\0';
	line = ft_strtrim(minish->line, " ");
	minish->cmdlst = create_node(NULL, NULL);
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
		if_tab_or_space(minish, i, &line, 0);
		if (line[i] == '|')
		{
			ch_str[0] = '|';
			if (line[i - 1] != ' ')
				set_free((void **)&line,replace_subst(line, ch_str, " |", i++));
			if (line[i + 1] && line[i + 1] != ' ')
				set_free((void **)&line,replace_subst(line, ch_str, "| ", i));

		}
		i++;
	}
	minish->line = line;
	if_tab_or_space(minish, i, &line, 'e');

//	i = 0;
//
//	while (i < words_cntr)
//	{
//		printf("%s\n", minish->cmd_splited[i++]);
//	}
}
