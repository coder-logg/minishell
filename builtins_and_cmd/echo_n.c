#include "../minishell.h"

void	echo_n(char **cmd)
{
	int	i;
	int	cmd_len;

	i = 1;
	cmd_len = arr_len(cmd);
	if (cmd_len <= 2)
		return ;
	while (i++ < cmd_len)
	{
		printf("%s", cmd[i]);
	}
}