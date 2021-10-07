#include "../minishell.h"

int is_all_spaces(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] != ' ')
			return (-1);
		i++;
	}
	return (0);
}

void	*check_malloc(void *ptr)
{
	if (ptr == NULL)
		putstr_exit("malloc error\n");
	return (ptr);
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
	tmp = *var;
	*var = new;
	if (tmp)
		free(tmp);
}
