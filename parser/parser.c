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

	if ((*str)[i] != '\"' && (*str)[i] != '\'')
		return (i);
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
	char	**splited;
	char	*cmd;

	splited = check_malloc(ft_calloc(1, sizeof(char *)));
	cmd = check_malloc(ft_substr(prev_pipe, 0, msh->line + i - prev_pipe));
	if (!cmd || !splited)
		return (-1);
	splited[0] = NULL;
	lst_new = create_node(cmd, splited);
	if (!lst_new)
		return (-1);
	ft_lstadd_back(&msh->cmdlst, lst_new);
	return (0);
}

int	divide_by_pipe(t_minish *msh)
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
			if (is_control_chr(msh->line[i]) && !msh->line[i + 1])
				return (-1);
			if (msh->line[i] == '\'' || msh->line[i] == '"')
				i = skip_untill_chr(msh->line + i + 1, msh->line[i]) - msh->line;
			if (msh->line[i] == '|')
			{
				if (cmdlst_add_elm(msh, prev_pipe, i))
					return (-1);
				prev_pipe = msh->line + i + 1;
			}
			i++;
		}
		if ((i > 0 &&  msh->line[i - 1] != '|') || prev_pipe == msh->line)
			if (cmdlst_add_elm(msh, prev_pipe, i))
				return (-1);
	}
	else if (cmdlst_add_elm(msh, msh->line, ft_strlen(msh->line)))
			return (-1);
	return (0);
}

char **get_cmd_splited(char *cmd, t_cmd *structure)
{
	char	**cmd_splited;
	int		i;
	char	ch_str[2];
	int		prev_spc;
	int		tmp;

	i = 0;
	(void)structure;
	ch_str[1] = 0;
	cmd = ft_strdup(cmd);
	prev_spc = 0;
	cmd_splited = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '<' || cmd[i] == '>')
		{
			i = parse_redirect(&cmd, i, structure);
			continue;
		}
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			ch_str[0] = cmd[i];
			set_free((void **)&cmd, replace_subst(cmd, ch_str, "", i));
			if (!cmd)
				return (NULL);
			i = skip_untill_chr(cmd + i, ch_str[0]) - cmd;
			set_free((void **)&cmd, replace_subst(cmd, ch_str, "", i));
			if (!cmd)
				return (NULL);
			continue;
		}
		if (cmd[i] == ' ' || !cmd[i + 1])
		{
			tmp = i;
			if (!cmd[i + 1])
				tmp++;
			cmd_splited = strarr_add(cmd_splited, arr_len(cmd_splited),
									 ft_substr(cmd, prev_spc, tmp - prev_spc));
			if (!cmd_splited)
				return (NULL);
			prev_spc = i + 1;
		}
		i++;
	}
//	cmd_splited = strarr_add(cmd_splited, arr_len(cmd_splited),
//							 ft_substr(cmd, prev_spc, i - prev_spc));
	free(cmd);
	return (cmd_splited);
}


//todo check malloc error in subfunction
char *parse_line(char *cmd, char **env)
{
	int		i;
	char	ch_str[2];

	i = 0;
	ch_str[1] = '\0';
	ch_str[0] = '\t';
	set_free((void **)&cmd, ft_strtrim(cmd, " \t"));
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i = parse_quotes(&cmd, i, env);
		}
		else if (cmd[i] == '$')
		{
			i = read_env(&cmd, i, env);
			continue ;
		}
		else if (cmd[i] == '~' && cmd[i - 1] == ' '
				&& (cmd[i + 1] == '/' || cmd[i + 1] == ' ' || !cmd[i + 1]))
			set_free((void **)&cmd, replace_subst(cmd, "~",
												  getenv("HOME"), i));
		else if (cmd[i] == '\t')
		{
			set_free((void **)&cmd, replace_subst(cmd, ch_str, " ", i));
			continue ;
		}
		else if (cmd[i] == ' ')
			set_free((void **)&cmd, shrink_chs_one(cmd, i, ' '));
		i++;
	}
	return (cmd);
}

void	parser(t_minish *minish)
{
	t_list	*elem;
	t_cmd	*cast;

	set_free((void **)&minish->line, ft_strtrim(minish->line, " \t"));
	if (!minish->line || !minish->line[0])
		return ;
	if (divide_by_pipe(minish))
		return ;
	elem = minish->cmdlst;
	while (elem)
	{
		cast = elem->content;
		cast->rd_fds[0] = -1;
		cast->rd_fds[1] = -1;
		cast->cmd = parse_line(cast->cmd, minish->env);
		cast->cmd_splited = get_cmd_splited(cast->cmd, cast);
		if (!cast->cmd_splited)
			return ;
		elem = elem->next;
	}
	minish->line = parse_line(minish->line, minish->env);
}
