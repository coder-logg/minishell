/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:29:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/23 19:58:32 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo(char **cmd_splited)
{
	int	i;

	i = 1;
	if (!ft_strcmp(cmd_splited[1], "-n"))
		i = 2;
	while (cmd_splited[i])
	{
		ft_putstr_fd(cmd_splited[i++], 1);
		if (cmd_splited[i] != NULL)
			write (1, " ", 1);
	}
	if (ft_strcmp(cmd_splited[1], "-n") != 0)
		write (1, "\n", 1);
}
