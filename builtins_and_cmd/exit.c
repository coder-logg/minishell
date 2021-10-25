/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:01:02 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/25 17:06:32 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static u_int8_t	atoi_overflow(const char *str)
{
	int			i;
	int			minus;
	u_int64_t	num;

	i = 0;
	minus = 1;
	num = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i])
		num = (num * 10) + (str[i++] - '0');
	return (num * minus);
}

int	ft_exit(char **cmd_splited)
{
	if (cmd_splited_len(cmd_splited) > 2)
		return (0);
	if (cmd_splited_len(cmd_splited) == 1)
		exit(g_status);
	exit(atoi_overflow(cmd_splited[1]));
}
