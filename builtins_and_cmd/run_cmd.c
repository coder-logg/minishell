#include "../minishell.h"

/**
**	@brief	run script
**
**	@return	int	-1 if ft_stjoin problem, -3 if no such script
*/
static int run_script(char **cmd, char **env)
{
	char	*str_path;
	char	*str_command;
	str_path = getenv("PWD=");
	str_path = ft_strjoin(str_path, "/");
	str_command = ft_strjoin(str_path, cmd[0]);
	if (!str_path)
		return (error_return(STRJOIN_ERROR));
	execve(str_command, cmd, env);
	free(str_command);
	cmd_not_found(cmd[0], NO_FILE_OR_DIR);
	return (-3);
}

/**
**	@brief	run command
**
**	@return	int	-1 if ft_stjoin problem, -2 if no such command
*/
static int run_file(char **path, char **cmd, char **env)
{
	char	*str_path;
	char	*str_command;
	int		i;

	i = 0;
	while (path[i])
	{
		str_path = ft_strjoin(path[i++], "/");
		if (!str_path)
			return (error_return(STRJOIN_ERROR));
		str_command = ft_strjoin(str_path, cmd[0]);
		free(str_path);
		if (!str_command)
			return (error_return(STRJOIN_ERROR));
		execve(str_command, cmd, env);
	}
	free(str_command);
	cmd_not_found(cmd[0], CMD_NOT_FOUND);
	return (-2);
}

/**
**	@brief	run script or file(command)
**	
**	@param	path	pointer to paths
**	@param	cmd		pointer to command with parameters
**	@param	env		environment
**	@return	int		-2 if no such cmd, -3 if no scipt, -1 if ft_strjoin problem 
*/
static int	script_or_file(char **path, char **cmd, char **env)
{
	if (ft_strchr(cmd[0], '.') != 0 && ft_strchr(cmd[0], '/') != 0)
		return (run_script(cmd, env));
	else
		return (run_file(path, cmd, env));
}

/**
**	@brief	create fork and run command via execve
**	
**	@param	cmd_str		line with command from readline
**	@param	env			environment
**	@return	int			-2 if no such cmd, -3 if no scipt, -1 if fork problem
*/
int	run_cmd(char **cmd, char **env)
{
	pid_t	pid;
	char	**path;
//	int		status;

	char *path_str = getenv("PATH");
	path_str += 5;
	path = ft_split(path_str, ':');
	pid = fork();
	if (pid < 0)
		return(error_return("Fork failed to create a new process."));
	else if (pid == 0)
		return (script_or_file(path, cmd, env));
	wait(&pid);
//	return (WEXITSTATUS(status));
	return 0;
}