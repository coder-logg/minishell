#include "../minishell.h"

static int parse_quotes(char **str, int i, char **env)
{
	char	quot;

	if ((*str)[i] != '\"' && (*str)[i] != '\'')
		return (i);
	quot = (*str)[i];
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && quot == '\"')
		{
			i = read_env(str, i, env);
			continue ;
		}
		if ((*str)[i] == quot)
			break ;
		i++;
	}
	return (i);
}

void	cmdlst_add_elm(t_minish *msh, const char *prev_pipe, int i)
{
	t_list	*lst_new;
	char	**splited;
	char	*cmd;

	splited = check_malloc(ft_calloc(1, sizeof(char *)));
	cmd = check_malloc(ft_substr(prev_pipe, 0, msh->line + i - prev_pipe));
	splited[0] = NULL;
	lst_new = create_node(cmd, splited);
	ft_lstadd_back(&msh->cmdlst, lst_new);
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
				i = skip_untill_chr(msh->line + i, msh->line[i]) - msh->line;
			if (msh->line[i] == '|')
			{
				cmdlst_add_elm(msh, prev_pipe, i);
				prev_pipe = msh->line + i + 1;
			}
			i++;
		}
		if ((i > 0 &&  msh->line[i - 1] != '|') || prev_pipe == msh->line)
			cmdlst_add_elm(msh, prev_pipe, i);
	}
	else
		cmdlst_add_elm(msh, msh->line, ft_strlen(msh->line));
}

char	**get_cmd_splited(char *cmd)
{
	char	**cmd_splited;
	int	i;
	char	ch_str[2];
	int		prev_spc;

	i = 0;
	ch_str[1] = 0;
	cmd = ft_strdup(cmd);
	prev_spc = 0;
	cmd_splited = NULL;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			cmd_splited = strarr_add(cmd_splited, arr_len(cmd_splited),
									 ft_substr(cmd, prev_spc, i - prev_spc));
			prev_spc = i + 1;
		}
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			ch_str[0] = cmd[i];
			set_free((void **)&cmd, replace_subst(cmd, ch_str, "", i));
			i = skip_untill_chr(cmd, '"') - cmd;
			set_free((void **)&cmd, replace_subst(cmd, ch_str, "", i));
		}
		i++;
	}
	cmd_splited = strarr_add(cmd_splited, arr_len(cmd_splited),
							 ft_substr(cmd, prev_spc, i - prev_spc));
	return (cmd_splited);
}

char *papse_line(char *cmd, char **env)
{
	int		i;
	char	ch_str[2];

	i = 0;
	ch_str[1] = '\0';
	ch_str[0] = '\t';
	set_free((void **)&cmd, ft_strtrim(cmd, " \t"));
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
			i = parse_quotes(&cmd, i, env);
		if (cmd[i] == '$')
		{
			i = read_env(&cmd, i, env);
			continue ;
		}
		if (cmd[i] == '~')
			set_free((void **)&cmd, replace_subst(cmd, "~",
												  getenv("HOME"), i));
		if (cmd[i] == '\t')
			set_free((void **)&cmd, replace_subst(cmd, ch_str, " ", i));
		if (cmd[i] == ' ')
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
	if (!minish->line[0])
		return ;
	divide_by_pipe(minish);
	elem = minish->cmdlst;
	while (elem)
	{
		cast = elem->content;
		cast->cmd = papse_line(cast->cmd, minish->env);
		cast->cmd_splited = get_cmd_splited(cast->cmd);
		elem = elem->next;
	}
	minish->line = papse_line(minish->line, minish->env);
}
