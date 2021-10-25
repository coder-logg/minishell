/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 19:29:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/25 21:13:59 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief		write status and string after status
**	@return	int	1 if problem with malloc, else 0
*/
static int	echo_status(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 2;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_str)
		return (1);
	ft_putnbr_fd(g_status, 1);
	while (str[i])
	{
		new_str[j] = str[i];
		j++;
		i++;
	}
	new_str[j] = '\0';
	ft_putstr_fd(new_str, 1);
	free(new_str);
	return (0);
}

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
	_Bool	flag;

	check_n(&flag, cmd_splited, &i);
	while (cmd_splited[i])
	{
		if (!ft_strncmp(cmd_splited[i], "$?", 2))
		{
			if (echo_status(cmd_splited[i]))
				return (1);
		}
		else
			ft_putstr_fd(cmd_splited[i], 1);
		i++;
		if (cmd_splited[i] != NULL)
			write (1, " ", 1);
	}
	if (flag == false)
		write (1, "\n", 1);
	return (0);
}
