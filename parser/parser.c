#include "../minishell.h"

bool is_control_chr(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

int parse_quotes(char **str, int i, char **env)
{
	char	quot;
	char	*tmp;

	if ((*str)[i] != '\"' && (*str)[i] != '\'')
		return (i);
	if ((*str)[i] == (*str)[i + 1])
	{
		tmp = chrdup((*str)[i + 1], 2);
		set_free((void **)str, replace_substr(*str, tmp, "", i));
		free(tmp);
		return (i);
	}
	quot = (*str)[i++];
	while ((*str)[i] && (*str)[i] != quot)
	{
		if ((*str)[i] == '$' && quot == '\"')
		{
			i = read_env(str, i, env);
			continue ;
		}
		i++;
	}
	return (i);
}

int	cmdlst_add_elm(t_minish *msh, const char *prev_pipe, int i)
{
	t_list	*lst_new;
	char	*cmd;

	cmd = chmllc(ft_substr(prev_pipe, 0, msh->line + i - prev_pipe));
	lst_new = create_node(cmd, NULL);
	ft_lstadd_back(&msh->cmdlst, lst_new);
	return (0);
}

void	divide_by_pipe(t_minish *msh)
{
	char	*prev_pipe;
	int		i;

	i = 0;
	prev_pipe = ft_strchr(msh->line, '|');
	if (prev_pipe)
	{
		prev_pipe = msh->line;
		while (msh->line[i])
		{
			if (msh->line[i] == '\'' || msh->line[i] == '"')
				i = skip_untill_chr(msh->line + i + 1, msh->line[i]) - msh->line;
			if (msh->line[i] == '|')
			{
				cmdlst_add_elm(msh, prev_pipe, i);
				prev_pipe = msh->line + i + 1;
			}
			i++;
		}
		if ((i > 0 && msh->line[i - 1] != '|') || prev_pipe == msh->line)
			cmdlst_add_elm(msh, prev_pipe, i);
	}
	else
		cmdlst_add_elm(msh, msh->line, ft_strlen(msh->line));
}

void	get_cmd_splited(char *cmd, t_cmd *structure, char **env, char ***dst)
{
	char	**cmd_splited;
	int		i;
	int		prev_spc;
	char	ch;

	i = 0;
	cmd = ft_strdup(cmd);
	prev_spc = 0;
	cmd_splited = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			i = parse_redirect(&cmd, i, structure, env);
			if (i == -2)
				return ;
			continue;
		}
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			ch = cmd[i];
			set_free((void **)&cmd, replace_substr(cmd, chstr(ch), "", i));
			i = skip_untill_chr(cmd + i, ch) - cmd;
			set_free((void **)&cmd, replace_substr(cmd, chstr(ch), "", i));
			continue;
		}
		if (cmd[i] == ' ')
		{
			cmd_splited = strarr_add(cmd_splited, arr_len(cmd_splited),
							chmllc(ft_substr(cmd, prev_spc, i - prev_spc)));
			prev_spc = i + 1;
		}
		i++;
	}
	if (prev_spc < i)
		cmd_splited = strarr_add(cmd_splited, arr_len(cmd_splited),
					 chmllc(ft_substr(cmd, prev_spc, i - prev_spc)));
	free(cmd);
	*dst = cmd_splited;
}


//todo check malloc error in subfunction
char *parse_line(char *cmd, char **env)
{
	int		i;
	int		index;

	i = 0;
	set_free((void **)&cmd, ft_strtrim(cmd, " \t"));
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i = parse_quotes(&cmd, i, env);
		else if (cmd[i] == '$')
		{
			i = read_env(&cmd, i, env);
			if (cmd[i] == ' ')
				set_free((void **)&cmd, shrink_chs_one(cmd, i - 1, ' '));
			continue ;
		}
		else if (cmd[i] == '~' && cmd[i - 1] == ' '
				&& (cmd[i + 1] == '/' || cmd[i + 1] == ' ' || !cmd[i + 1]))
		{
			index = get_envi(env,"HOME");
			if (index == -1)
				set_free((void **)&cmd, replace_substr(cmd, "~", "", i));
			else
				set_free((void **)&cmd, replace_substr(cmd, "~", env[index] +
					ft_strlen("HOME="), i));
		}
		i++;
	}
	return (cmd);
}

int	preparser(char **line)
{
	int		i;
	bool	flag;

	set_free((void **)line, chmllc(ft_strtrim(*line, " \t")));
	if (!(*line)[0])
		return (0);
	i = -1;
	flag = false;
	while ((*line)[++i])
	{
		if (((*line)[i] == '>' || (*line)[i] == '<') && (*line)[i] == (*line)[i + 1])
			i++;
		if (is_control_chr((*line)[i]))
		{
			if (flag)
				return (print_sintaxerr((*line)[i]));
			else
				flag = true;
			continue;
		}
		else if ((*line)[i] != ' ' && (*line)[i] != '\t')
			flag = false;
		if ((*line)[i] == '\'' || (*line)[i] == '"')
			i = skip_untill_chr(*line + i + 1, (*line)[i]) - *line;
		else if ((*line)[i] == '\t')
		{
			set_free((void **)line, replace_substr(*line, chstr('\t'), " ", i));
			continue ;
		}
		else if ((*line)[i] == ' ')
			set_free((void **)line, shrink_chs_one(*line, i, ' '));
	}
	if (flag)
		return (print_sintaxerr((*line)[i]));
	return (0);
}

int	parser(t_minish *minish)
{
	t_list	*elem;
	t_cmd	*cast;
	int		status;

	signal_pipes_cmd();
	if (preparser(&minish->line))
		return (-1);
	divide_by_pipe(minish);
	elem = minish->cmdlst;
	status = 0;
	while (elem)
	{
		cast = elem->content;
		cast->cmd = parse_line(cast->cmd, minish->env);
		get_cmd_splited(cast->cmd, cast, minish->env, &cast->cmd_splited);
		if (!cast->cmd_splited || status)
			break ;
		elem = elem->next;
	}
	minish->line = parse_line(minish->line, minish->env);
	main_signals();
	return (status);
}


// static int	preparser2(char **line, bool *flag)
// {
// 	set_free((void **)line, chmllc(ft_strtrim(*line, " \t")));
// 	if (!(*line)[0])
// 		return (0);
// 	*flag = false;
// 	return (-1);
// }

// static int	preparser(char **line, bool flag, int i)
// {
// 	i = preparser2(line, &flag);
// 	while ((*line)[++i])
// 	{
// 		if (((*line)[i] == '>' || (*line)[i] == '<') && (*line)[i] == (*line)[i + 1])
// 			i++;
// 		if (is_control_chr((*line)[i]))
// 		{
// 			if (flag)
// 				return (print_sintaxerr((*line)[i]));
// 			else
// 				flag = true;
// 			continue;
// 		}
// 		else if ((*line)[i] != ' ' && (*line)[i] != '\t')
// 			flag = false;
// 		if ((*line)[i] == '\'' || (*line)[i] == '"')
// 			i = skip_untill_chr(*line + i + 1, (*line)[i]) - *line;
// 		else if ((*line)[i] == '\t')
// 		{
// 			set_free((void **)line, replace_substr(*line, chstr('\t'), " ", i));
// 			continue ;
// 		}
// 		else if ((*line)[i] == ' ')
// 			set_free((void **)line, shrink_chs_one(*line, i, ' '));
// 	}
// 	if (flag)
// 		return (print_sintaxerr((*line)[i]));
// 	return (0);
// }