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
