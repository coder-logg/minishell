/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:37:12 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/03 01:55:51 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_path(char **env)
{
	char	**path;
	char	*path_str;
	int		i;

	i = 0;
	while (ft_strstr(env[i], "PATH=") == 0)
		i++;
	path_str = env[i];
	path_str += 5;
	path = ft_split(path_str, ':');
	if (!path)
	{
		g_status = 1;
		exit(EXIT_FAILURE);
	}
	return (path);
}

static void check(char *str)
{
	if (!str)
	{
		g_status = 1;
		exit(EXIT_FAILURE);
	}
}

/**
**	@brief	run command
**	@return	int	-1 if ft_stjoin problem, -2 if no such command
*/
void	run_cmd(char **cmd, char **env)
{
	char	*str_path;
	char	*str_command;
	char	**path;
	int		i;

	i = 0;
	path = get_path(env);
	while (path[i])
	{
		str_path = ft_strjoin(path[i++], "/");
		if (!str_path)
			check(str_path);
		str_command = ft_strjoin(str_path, cmd[0]);
		free(str_path);
		check(str_command);
		if (!access(str_command, F_OK))
		{
			execve(str_command, cmd, env);
			g_status = 1;
			perror_exit_bash(cmd[0]);
		}
	}
	g_status = 1;
	command_exit(cmd[0], "command not found", CMD_NOT_FOUND);
}
