/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:18:52 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/22 11:51:43 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief	wait all cahild processes in parent process
*/
static void wait_all_process(t_list	*head)
{
	while (head)
	{
		waitpid(((t_cmd *)head->content)->pid, NULL, 0);
		head = head->next;
	}
}

/**
**	@brief	close all fd if it's not a 0/1/2
*/
void close_pipes(t_list	*elem)
{
	while (elem)
	{
		if (((t_cmd *)elem->content)->fd_in > 2)
			close(((t_cmd *)elem->content)->fd_in);
		if (((t_cmd *)elem->content)->fd_out > 2)
			close(((t_cmd *)elem->content)->fd_out);
		elem = elem->next;
	}
}

/**
**	@brief					create fork & executes the command or builtin & close pipes
**	@param	elem			struct with command
**	@param	next_fd_in		fd_in for next command
*/
static void	process(char **env, t_list *elem, int next_fd_in)
{
	char *pwd;

	pwd = ft_calloc(4096, 1);
	next_fd_in = 0;
	((t_cmd *)elem->content)->pid = fork();
	if (((t_cmd *)elem->content)->pid < 0)
		return ;
	if (((t_cmd *)elem->content)->pid == 0)
	{
		// printf("Какие дескрипторы использует команда %s  %d , %d\n", ((t_cmd *)elem->content)->cmd, ((t_cmd *)elem->content)->fd_out, ((t_cmd *)elem->content)->fd_in);
		if (next_fd_in > 2)
			close(next_fd_in);
		if (dup2(((t_cmd *)elem->content)->fd_out, STDOUT_FILENO) == -1)
			perror_exit("dup2");
		if (distribution(NULL, ((t_cmd *)elem->content)->cmd_splited, env))
			exit (0);
		if (dup2(((t_cmd *)elem->content)->fd_in, STDIN_FILENO) == -1)
			perror_exit("dup2");
		close_pipes(elem);
		run_cmd(((t_cmd *)elem->content)->cmd_splited, env);
	}
}

/**
**	@brief		create pipes for all commands
*/
void	do_pipes(t_list *elem, char **env)
{
	int fd[2];

	while (elem)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = STDOUT_FILENO;
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

/**
**	@brief		run commands and builtins with pipes
*/
void	ft_pipes(t_minish *minish, char **env)
{
	t_list	*elem;
	t_list	*head;
	
	elem = minish->cmdlst;
	head = elem;
	((t_cmd *)elem->content)->fd_out = STDOUT_FILENO;
	((t_cmd *)elem->content)->fd_in = STDIN_FILENO;
	do_pipes(elem, env);
	elem = head;
	close_pipes(elem);
	wait_all_process(head);
}
