/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:37:12 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/21 16:58:19 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_path(void)
{
	char	**path;
	char	*path_str;

	path_str = getenv("PATH=");
	path = ft_split(path_str, ':');
	if (!path)
		exit(EXIT_FAILURE);
	return (path);
}
/**
**	@brief	run command
**
**	@return	int	-1 if ft_stjoin problem, -2 if no such command
*/
void	run_cmd(char **cmd, char **env)
{
	char	*str_path;
	char	*str_command;
	char	**path;
	int		i;

	i = 0;
	path = get_path();
	while (path[i])
	{
		str_path = ft_strjoin(path[i++], "/");
		if (!str_path)
			exit(EXIT_FAILURE);
		str_command = ft_strjoin(str_path, cmd[0]);
		free(str_path);
		if (!str_command)
			exit(EXIT_FAILURE);
		if (!access(str_command, F_OK))
		{
			execve(str_command, cmd, env);
			perror_exit_bash(cmd[0]);
		}
	}
	command_exit(cmd[0], "command not found", CMD_NOT_FOUND);
}
