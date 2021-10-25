/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:29:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/25 16:48:38 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(char **cmd_splited)
{
	int		i;
	int		len;
	_Bool	flag;

	i = 1;
	len = 0;
	flag = false;
	while (cmd_splited[len])
		len++;
	if (len != 1 && !ft_strcmp(cmd_splited[1], "-n"))
	{
		i = 2;
		flag = true;
	}
	if (len > 1)
		while (cmd_splited[i])
		{
			ft_putstr_fd(cmd_splited[i++], 1);
			if (cmd_splited[i] != NULL)
				write (1, " ", 1);
		}
	if (flag == false)
		write (1, "\n", 1);
	return (0);
}
