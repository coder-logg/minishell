#include "../minishell.h"

int	echo_n(char **cmd)
{
	int	i;
	int	cmd_len;

	i = 1;
	cmd_len = arr_len(cmd);
	if (cmd_len <= 2)
		return (0);
	while (i++ < cmd_len)
	{
		printf("%s", cmd[i]);
	}
	return (0);
}