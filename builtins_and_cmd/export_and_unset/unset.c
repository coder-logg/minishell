/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:44:46 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/02 04:25:07 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int boo(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset(char **cmd_splited, char **env, t_minish *minish)
{
	(void)cmd_splited;
	(void)env;
	// (void)minish;
	int i;
	i = 0;
	int j = 1;
	while (cmd_splited[j])
	{
		if (!boo(cmd_splited[j]))
			return (1);
		j++;
	}
	j = 1;
	while (cmd_splited[j])
	{
		while (minish->env[i])
		{
			if (ft_strncmp(minish->env[i], cmd_splited[j], ft_strlen(cmd_splited[j])))
			{
				free(minish->env[i]);
				break ;
			}
			i++;
		}
		j++;
	}
	return (0);
}
