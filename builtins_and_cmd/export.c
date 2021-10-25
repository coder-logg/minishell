/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:28:32 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/24 18:02:08 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_export(char **cmd_splited, char **env)
{
	int	i;

	i = 0;
	(void)cmd_splited;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
	}
}
