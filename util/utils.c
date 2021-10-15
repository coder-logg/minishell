#include "../minishell.h"

void	*check_malloc(void *ptr)
{
	if (ptr == NULL)
		putstr_exit("malloc error\n");
	return (ptr);
}

t_list	*create_node(char *cmd, char **cmd_splited)
{
	t_cmd	*elem;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	check_malloc(elem);
	elem->cmd = cmd;
	elem->cmd_splited = cmd_splited;
	return (check_malloc(ft_lstnew(elem)));
}

void destroy_node(void *content)
{
	t_cmd	*cast;
	int		i;

	i = 0;
	cast = (t_cmd *)content;
	set_free((void **)&cast->cmd, NULL);
	while (i < arr_len(((t_cmd *)content)->cmd_splited))
	{
		free(((t_cmd *)content)->cmd_splited[i]);
		i++;
	}
	set_free((void **)&cast->cmd_splited, NULL);
}

/**
 * free <b><i>var</i></b> and set it <b><i>new</i></b>
 * @param var pointer to the variable with pointer that will be freed
 * @param new value that will be wrote to <b><i>var</i></b> after liberation
 */
void	set_free(void **var, void *new)
{
	void	*tmp;

	if (var == NULL)
		return ;
	if (*var == new)
		return ;
	tmp = *var;
	*var = new;
	if (tmp)
		free(tmp);
}
