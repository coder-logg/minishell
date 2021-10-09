#include "../minishell.h"

void	*check_malloc(void *ptr)
{
	if (ptr == NULL)
		putstr_exit("malloc error\n");
	return (ptr);
}

t_list	*create_node(char *cmd, char **cmd_splited)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_minish));
	new->cmd = cmd;
	new->cmd_splited = cmd_splited;
	return (ft_lstnew(new));
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
