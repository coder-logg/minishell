#include "../minishell.h"



/**
**	@brief		run script
**	@return		int	-1 if ft_stjoin problem, -3 if no such script
*/
static void run_script(char **cmd, char **env)
{
	char	*str_path;
	char	*str_command;

	if (cmd[0][0] == '/')
	{
		execve(cmd[0], cmd, env);
		g_status = 1;
		perror_exit_bash(cmd[0]);
	}
	else
	{
		str_path = getenv("PWD=");
		str_path = ft_strjoin(str_path, "/");
		str_command = ft_strjoin(str_path, cmd[0]);
		if (!str_command || !str_path)
		{
			g_status = 1;
			exit(EXIT_FAILURE);
		}
		execve(str_command, cmd, env);
		g_status = 1;
		perror_exit_bash(cmd[0]);
	}
}

/**
**	@brief			run script or file(command)
**	@return	int		-2 if no such cmd, -3 if no scipt, -1 if ft_strjoin problem 
*/
static void	script_or_file(char **cmd, char **env)
{
	
	if ((ft_strchr(cmd[0], '.') != 0 && ft_strchr(cmd[0], '/') != 0) ||
		ft_strchr(cmd[0], '/') != 0)
		run_script(cmd, env);
	else
		run_cmd(cmd, env);
}

/**
**	@brief			create fork and run command
**	@param	cmd		pointer to command with parameters
**	@return	int		-2 if no such cmd, -3 if no scipt, -1 if fork problem
*/
void	ft_command(char **cmd, char **env)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid < 0)
		return (perror_return("fork"));
	else if (pid == 0)
		script_or_file(cmd, env);
	if (pid > 0)
		wait(&pid);
}
