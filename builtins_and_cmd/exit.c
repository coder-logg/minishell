/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:01:02 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/03 15:48:54 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int return_status(int *ret, int num)
// {
// 	*ret = num;
// 	return (0);
// }
static int str_exit(char *str1, char *str, int exit_code)
{
	write(2, "bash: ", 6);
	write(2, "exit: ", 7);
	write(2, str1, ft_strlen(str1));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(exit_code);
}

static void	check_valid_status(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 1 && str[0] == '-')
		str_exit(str, "numeric argument required", 255);
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			str_exit(str, "numeric argument required", 255);
		i++;
	}
}

int	ft_exit(char **cmd_splited)
{
	if (arr_len(cmd_splited) > 2)
	{
		write (2, "bash: exit: too many arguments\n", 32);
		return (1);
	}
	if (arr_len(cmd_splited) == 1)
		exit(g_status);
	check_valid_status(cmd_splited[1]);
	exit(23);
	// exit(atoi_overflow(cmd_splited[1]) & 255);
	// return (atoi_overflow(cmd_splited[1]) & 255);
}
