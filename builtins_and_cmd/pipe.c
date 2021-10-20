/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:52 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/20 13:41:14 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec(char **cmd, char **env)
{
	char	*str_path;
	char	*str_command;
	char	*path_str;
	char	**path;
	int		i;

	i = 0;
	path_str = getenv("PATH=");
	path = ft_split(path_str, ':');
	if (!path)
		return (-1);
	while (path[i])
	{
		str_path = ft_strjoin(path[i++], "/");
		if (!str_path)
			error_return("error in ft_strjoin");
		str_command = ft_strjoin(str_path, cmd[0]);
		free(str_path);
		if (!str_command)
			error_return("error in ft_strjoin");
		if (!access(str_command, 0))
		{
			execve(str_command, cmd, env);
			exit(1);
		}
	}
	return (cmd_not_found(cmd[0], "command not found:"));
}

void close_pipes(t_list	*tmp)
{
	t_list *elem;

	elem = tmp;
	while (elem)
	{
		if (((t_cmd *)elem->content)->fd_in > 2)
			close(((t_cmd *)elem->content)->fd_in);
		if (((t_cmd *)elem->content)->fd_out > 2)
			close(((t_cmd *)elem->content)->fd_out);
		elem = elem->next;
	}
}

static int	process(char **cmd, char **env, t_list *elem, int fd_nelishnii)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_return("fork error");
	if (pid == 0)
	{	
		// printf("nelishnii == %d\n", fd_nelishnii);
		// printf("Какие дескрипторы использует команда %s  %d , %d\n", ((t_cmd *)elem->content)->cmd, ((t_cmd *)elem->content)->fd_out, ((t_cmd *)elem->content)->fd_in);
		if (fd_nelishnii > 2)
			close(fd_nelishnii);
		dup2(((t_cmd *)elem->content)->fd_out, 1);
		dup2(((t_cmd *)elem->content)->fd_in, 0);
		close_pipes(elem);
		if (ft_exec(cmd, env) == -1)
			return (-1);
	}
	// else if (pid > 0)
	// {
	// 	((t_cmd *)elem->content)->pid = pid;
	// }
	return (0);
}


int ft_pipes(t_minish *minish, char **env)
{
	t_list	*elem;
	t_list	*head;
	int fd[2];

	elem = minish->cmdlst;
	head = elem;
	while (elem)
	{
		((t_cmd *)elem->content)->fd_out = 1;
		((t_cmd *)elem->content)->fd_in = 0;
		elem = elem->next;
	}
	elem = head;
	while (elem)
	{
		fd[0] = 0;
		fd[1] = 1;
		if (elem->next)
			pipe(fd);
		// printf("%s   fd0 %d  fd1 %d\n", ((t_cmd *)elem->content)->cmd, fd[0], fd[1]);
		if (elem)
		{
			((t_cmd *)elem->content)->fd_out = fd[1];
			if (elem->next)
				((t_cmd *)elem->next->content)->fd_in = fd[0];
		}
		process(((t_cmd *)elem->content)->cmd_splited, env, elem, fd[0]);
		if (((t_cmd *) elem->content)->fd_out > 2)
			close(((t_cmd *) elem->content)->fd_out);
		elem = elem->next;
	}
	close_pipes(head);
	while (head)
	{
		waitpid(0, NULL, 0);
		head = head->next;
	}
	return (0);
}
