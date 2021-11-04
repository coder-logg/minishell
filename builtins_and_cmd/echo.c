/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:29:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/04 05:55:06 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid_n(char *str, int *flag)
{
	unsigned int i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (i == ft_strlen(str))
	{
		*flag = 1;
		return (i);
	}
	return (0);
}

/**
**	@brief		echo builtin
**	@return	int	1 if problem with malloc, else 0
*/
int	echo(char **cmd_splited)
{
	int		i;
	int flag;

	i = 1;
	flag = 0;
	if (arr_len(cmd_splited) > 1)
		if (cmd_splited[1][0] == '-' && cmd_splited[1][1] == 'n')
			while (cmd_splited[i] && check_valid_n(cmd_splited[i], &flag))
				i++;
	while (cmd_splited[i])
	{
		ft_putstr_fd(cmd_splited[i], 1);
		i++;
		if (cmd_splited[i] != NULL)
			write (1, " ", 1);
	}
	if (flag == 0)
		write (1, "\n", 1);
	return (0);
}
