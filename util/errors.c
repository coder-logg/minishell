#include "../minishell.h"


/**
**	@brief	display error with ": too many arguments" from str in 2 fd
**	
**	@param	str		display error
*/
void error_builtin(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": too many arguments", 20);
	write(2, "\n", 1);
}

/**
**	@brief	display error with "bash: " from str in 2 fd
**	
**	@param	cmd		command
**	@param	str		display error
*/
int cmd_not_found(char *cmd, char *str)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (-1);
}

/**
**	@brief	display error with "bash: " from str in 2 fd and exit
**	
**	@param	cmd		command
**	@param	str		display error
**	@return			exit with -1
*/
int command_exit(char *cmd, char *str, int exit_code)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(exit_code);
}

/**
**	@brief	executes the perror and exit with errno
**	
**	@param	str		display error
*/
void	perror_exit_bash(char *str)
{
	write(2, "bash: ", 6);
	if (str)
		perror(str);
	else
		perror(NULL);
	exit(errno);
}