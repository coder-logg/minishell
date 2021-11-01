/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:28:32 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/01 13:44:53 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	sort_env(char **export, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strcmp(export[j], export[j + 1]) > 0)
			{
				tmp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	just_export(char **env)
{
	int		i;
	char	**export;

	export = ft_calloc(sizeof(char *), (arr_len(env) + 1));
	if (!export)
		return (1);
	i = -1;
	while (env[++i])
	{
		export[i] = ft_strdup(env[i]);
		if (!export[i])
			return (1);
	}
	export[i] = NULL;
	sort_env(export, arr_len(env));
	print_export(export);
	i = 0;
	while (export[i])
		free(export[i++]);
	free(export);
	return (0);
}

int	check_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (0);
	while (str[i])
	{
		if (str[i] == '?' || str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

char **add_export(char **cmd_splited, char **env)
{
	int		i;
	int		k;
	char	**export;

	i = 1;
	k = 0;
	while (cmd_splited[i])
	{
		if (check_valid(cmd_splited[i]))
			k++;
		i++;
	}
	export = ft_calloc(sizeof(char *), (arr_len(env) + k + 1));
	i = 0;
	while (env[i])
	{
		export[i] = ft_strdup(env[i]);
		if (!export[i])
			return (NULL);
		i++;
	}
	k = 1;
	while (cmd_splited[k])
	{
		if (check_valid(cmd_splited[k]))
		{
			export[i] = ft_strdup(cmd_splited[k]);
			if (!export[i])
				return (NULL);
			i++;
		}
		else
			cmd_not_found(cmd_splited[k], "not a valid identifier");
		k++;
	}
	export[i] = NULL;
	return (export);
}

int	ft_export(char **cmd_splited, char **env, t_minish *minish)
{
	if (arr_len(cmd_splited) == 1)
		return (just_export(env));
	minish->env = add_export(cmd_splited, env);
	free_arr(env);
	return (0);
}
