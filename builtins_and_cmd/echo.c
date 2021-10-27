/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:29:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/27 21:52:43 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief	check -n after echo
*/
static void	check_n(_Bool *flag, char **cmd_splited, int *i)
{
	*i = 1;
	if (cmd_splited_len(cmd_splited) > 1 && !ft_strcmp(cmd_splited[1], "-n"))
	{
		(*i) = 2;
		*flag = true;
	}
	else
		*flag = false;
}

/**
**	@brief		echo builtin
**	@return	int	1 if problem with malloc, else 0
*/
int	echo(char **cmd_splited)
{
	int		i;
	bool	flag;

	check_n(&flag, cmd_splited, &i);
	while (cmd_splited[i])
	{
		ft_putstr_fd(cmd_splited[i], 1);
		i++;
		if (cmd_splited[i] != NULL)
			write (1, " ", 1);
	}
	if (flag == false)
		write (1, "\n", 1);
	return (0);
}
