/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 23:18:14 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/01 15:26:24 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	putstr_in_export(char *export)
{
	int	i;

	i = 0;
	while (export[i] != '=')
	{
		write(1, &export[i], 1);
		i++;
	}
	write(1, &export[i], 1);
	i++;
	write(1, "\"", 1);
	while (export[i])
	{
		write(1, &export[i], 1);
		i++;
	}
	write(1, "\"", 1);
	write(1, "\n", 1);
}

void	print_export(char **export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strncmp(export[i], "_=", 2) != 0)
		{
			if (ft_strchr(export[i], '='))
				putstr_in_export(export[i]);
			else
				ft_putendl_fd(export[i], 1);
		}
		i++;
	}
}
