#include "../minishell.h"


/**
**	@brief			display error with ": too many arguments" from str in 2 fd
**	@param	str		display error
**	@return	int		0
*/
int error_builtin(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": too many arguments", 20);
	write(2, "\n", 1);
	return (0);
}

/**
**	@brief			display error with "bash: " from str in 2 fd
**	@param	cmd		command
**	@param	str		display error
**	@param	str2	display error2, may be NULL
*/
int cmd_not_found(char *cmd, char *str, char *str2)
{
	write(2, "msh: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	if (str2 != NULL)
	{
		write(2, ": ", 2);
		write(2, str2, ft_strlen(str2));
	}
	write(2, "\n", 1);
	return (-1);
}

/**
**	@brief			display error with "bash: " from str in 2 fd and exit
**	@param	cmd		command
**	@param	str		display error
**	@return			exit with -1
*/
int command_exit(char *cmd, char *str, int exit_code)
{
	write(2, "msh: ", 5);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(exit_code);
}

/**
**	@brief			executes the perror and exit with errno
**	@param	str		display error
*/
void	perror_exit_bash(char *str)
{
	write(2, "msh: ", 5);
	if (str)
		perror(str);
	else
		perror(NULL);
	exit(errno);
}

int print_sintaxerr(char err_chr)
{
	char	ch_str[2];

	ch_str[1] = 0;
	g_status = SYNTAX_ERROR;
	ft_putstr_fd("msh: syntax error near unexpected token '", 2);
	if (!err_chr)
		ft_putstr_fd("newline'\n", 2);
	else
	{
		ch_str[0] = err_chr;
		ft_putstr_fd(ch_str, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (-1);
}
