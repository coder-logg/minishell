/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:52 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/21 13:39:59 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	process(char **env, t_list *elem, int next_fd_in)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		// printf("nelishnii == %d\n", fd_nelishnii);
		// printf("Какие дескрипторы использует команда %s  %d , %d\n", ((t_cmd *)elem->content)->cmd, ((t_cmd *)elem->content)->fd_out, ((t_cmd *)elem->content)->fd_in);
		if (next_fd_in > 2)
			close(next_fd_in);
		if (dup2(((t_cmd *)elem->content)->fd_out, 1) == -1)
			perror_exit("dup2");
		if (dup2(((t_cmd *)elem->content)->fd_in, 0) == -1)
			perror_exit("dup2");
		close_pipes(elem);
		run_cmd(((t_cmd *)elem->content)->cmd_splited, env);
	}
	// else if (pid > 0)
	// 	((t_cmd *)elem->content)->pid = pid;
}

void	do_pipes(t_list *elem, char **env)
{
	int fd[2];

	while (elem)
	{
		fd[0] = 0;
		fd[1] = 1;
		if (elem->next)
			pipe(fd);
		// printf("%s   fd0 %d  fd1 %d\n", ((t_cmd *)elem->content)->cmd, fd[0], fd[1]);
		((t_cmd *)elem->content)->fd_out = fd[1];
		if (elem->next)
			((t_cmd *)elem->next->content)->fd_in = fd[0];
		process(env, elem, fd[0]);
		if (((t_cmd *) elem->content)->fd_out > 2)
			close(((t_cmd *)elem->content)->fd_out);
		elem = elem->next;
	}
}

void	ft_pipes(t_minish *minish, char **env)
{
	t_list	*elem;
	t_list	*head;

	elem = minish->cmdlst;
	head = elem;
	while (elem)
	{
		((t_cmd *)elem->content)->fd_out = 1;
		((t_cmd *)elem->content)->fd_in = 0;
		elem = elem->next;
	}
	elem = head;
	do_pipes(elem, env);
	close_pipes(head);
	while (head)
	{
		waitpid(0, NULL, 0);
		head = head->next;
	}
}
