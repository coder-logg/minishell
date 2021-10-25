/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 18:01:02 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/25 18:11:36 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **cmd_splited)
{
	if (cmd_splited_len(cmd_splited) > 2)
		return (0);
	if (cmd_splited_len(cmd_splited) == 1)
		exit(g_status);
	exit(atoi_overflow(cmd_splited[1]) & 255);
}
