/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:10:22 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/24 20:55:36 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
**	@brief		env builtin
**	@param		cmd_splited		command
**	@return	int	0
*/
int		ft_env(char **cmd_splited, char **env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (cmd_splited[len])
		len++;
	if (len > 1)
		return (error_builtin(cmd_splited[0]));
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}