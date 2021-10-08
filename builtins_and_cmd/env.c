/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:22 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/04 21:47:22 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	@brief	env builtin
*/
void ft_env(t_minish *minish, char **env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (minish->cmd[len])
		len++;
	if (len > 1)
	{
		error_builtin(minish->cmd[0]);
		return ;
	}
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}