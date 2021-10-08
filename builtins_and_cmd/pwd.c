/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:01 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/04 21:47:05 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	@brief	pwd builtin
*/
void ft_pwd(t_minish *minish)
{
	char *str;
	int len;

	len = 0;
	while (minish->cmd[len])
		len++;
	if (len > 1)
	{
		error_builtin(minish->cmd[0]);
		return ;
	}
	str = getenv("PWD");
	ft_putendl_fd(str, 1);
}
