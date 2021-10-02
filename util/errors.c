#include "../minishell.h"

void error_builtin(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": too many arguments", 20);
	write(2, "\n", 1);
}

void cmd_not_found(char *cmd)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found", 19);
	write(2, "\n", 1);
}