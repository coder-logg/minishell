#include "../minishell.h"

int	arr_len(char **cmd_splited)
{
	int	i;

	i = 0;
	while (cmd_splited[i] != NULL)
		i++;
	return (i);
}

void	*resize_strarr(char **arr, size_t arr_len)
{
	char	**new_arr;

//	if (arr_len > 0)
		new_arr = (char	**)check_malloc(ft_calloc(arr_len + 2, sizeof(char *)));
//	else
//		new_arr = (char	**)check_malloc(ft_calloc(2, sizeof(char *)));
	if (arr_len >= 1)
		ft_memcpy(new_arr, arr, sizeof(char *) * (arr_len + 1));
	new_arr[arr_len + 1] = NULL;
	free(arr);
	return (new_arr);
}

static int parse_quotes(char **str, int i)
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
	char	quot;

	i = 0;
	prev_pipe = ft_strchr(msh->line, '|');
	if (prev_pipe)
	{
		prev_pipe = msh->line;
		while (msh->line[i])
		{
			if (msh->line[i] == '\'' || msh->line[i] == '"')
			{
				quot = msh->line[i];
				while (msh->line[i] && msh->line[i] != quot)
					i++;
			}
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

static void if_tab_or_space(t_cmd *lst_cont, int i, char **cmd)
{
	static int	prev_spc = 0;
	static int	cmd_splited_len = 0;
	char		ch_str[2];

	ch_str[1] = '\0';
	if (i == 0)
	{
		cmd_splited_len = 0;
		prev_spc = 0;
	}
	if ((*cmd)[i] == '\t')
	{
		ch_str[0] = '\t';
		set_free((void **)cmd, replace_subst(*cmd, ch_str, " ", i));
	}
	if ((*cmd)[i] == ' ' || !(*cmd)[i + 1]) // maybe error
	{
		if (!(*cmd)[i + 1])
			i++;
		set_free((void **)cmd, shrink_chs_one(*cmd, i, ' '));
		if (lst_cont)
		{
			lst_cont->cmd_splited = resize_strarr(lst_cont->cmd_splited,
												  arr_len(lst_cont->cmd_splited));
			(lst_cont->cmd_splited[cmd_splited_len++]) = check_malloc(
					ft_substr(*cmd + prev_spc, 0, i - prev_spc));
			prev_spc = i + 1;
		}
	}
}

char	*parse_to_cmd_splited(t_cmd *lst_elm, char *cmd)
{
	int i;

	i = 0;
	set_free((void **)&cmd, ft_strtrim(cmd, " \t"));
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i = parse_quotes(&cmd, i);
			continue ;
		}
		if (cmd[i] == '$')
		{
			i = read_env(&cmd, i);
			continue ;
		}
		if_tab_or_space(lst_elm, i, &cmd);
		i++;
	}
	if (!ft_strchr(cmd, ' ') && lst_elm)
	{
		lst_elm->cmd_splited = resize_strarr(lst_elm->cmd_splited, 0);
		lst_elm->cmd_splited[0] = ft_strdup(cmd);
	}
	return (cmd);
}

void parser(t_minish *minish)
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
		cast->cmd = parse_to_cmd_splited(cast, cast->cmd);
		elem = elem->next;
	}
	minish->line = parse_to_cmd_splited(NULL, minish->line);
//	elem = minish->cmdlst;
//	while (elem)
//	{
		// printf("{cmd : \"%s\",  ", ((t_cmd *)elem->content)->cmd);
//		int i = 0;
//		printf("cmd_splited : {");
//		while (i < arr_len(((t_cmd *)elem->content)->cmd_splited))
//		{
//			printf("\"%s\", ", ((t_cmd *)elem->content)->cmd_splited[i]);
//			i++;
//		}
//		printf("}}\n");
//		elem = elem->next;
//	}
}
