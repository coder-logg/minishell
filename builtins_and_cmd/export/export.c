/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:28:32 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/27 23:19:19 by cvenkman         ###   ########.fr       */
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

	export = malloc(sizeof(char *) * (cmd_splited_len(env) + 1));
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
	sort_env(export, cmd_splited_len(env));
	print_export(export);
	i = 0;
	while (export[i])
		free(export[i++]);
	free(export);
	return (0);
}

int	ft_export(char **cmd_splited, char **env)
{
	if (cmd_splited_len(cmd_splited) == 1)
		return (just_export(env));
	return (0);
}
