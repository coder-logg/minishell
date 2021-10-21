/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:01 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/21 00:40:11 by tphlogis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief	pwd builtin
*/
void	ft_pwd(char **cmd_splited)
{
	char *buf;
	int len;

	len = 0;
	while (cmd_splited[len])
		len++;
	if (len > 1)
	{
		error_builtin(cmd_splited[0]);
		return ;
	}
	buf = check_malloc(ft_calloc(1024, sizeof(char)));
	getcwd(buf, 1024);
	ft_putendl_fd(buf, 1);
	free(buf);
}
