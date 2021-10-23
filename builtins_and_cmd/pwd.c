/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:01 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/22 13:17:10 by tphlogis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief	pwd builtin
*/
void ft_pwd(char **cmd_splited)
{
	char	*pwd;
	int		len;

	len = 0;
	pwd = ft_calloc(4096, 1);
	while (cmd_splited[len])
		len++;
	if (len > 1)
	{
		error_builtin(cmd_splited[0]);
		return ;
	}
	getcwd(pwd, 4096);
	ft_putendl_fd(pwd, 1);
	free(pwd);
}
