/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:01 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/16 19:31:20 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief	pwd builtin
*/
void ft_pwd(char **cmd_splited)
{
	char *str;
	int len;

	len = 0;
	while (cmd_splited[len])
		len++;
	if (len > 1)
	{
		error_builtin(cmd_splited[0]);
		return ;
	}
	str = getenv("PWD");
	ft_putendl_fd(str, 1);
}
