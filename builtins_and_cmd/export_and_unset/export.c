/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:28:32 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/02 04:24:10 by cvenkman         ###   ########.fr       */
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

int	copy_same_key(char *str, char **export)
{
	int	y;
	int	key_len;
	int	env_key_len;

	y = 0;
	key_len = 0;
	while (str[key_len] != '=')
		key_len++;
	while (export[y])
	{
		env_key_len = 0;
		while(export[y][env_key_len] != '\0' && export[y][env_key_len] != '=')
			env_key_len++;
		if (env_key_len == key_len)
			if (ft_strncmp(str, export[y], key_len) == 0)
			{
				free(export[y]);
				export[y] = ft_strdup(str);
				break ;
			}
		y++;
	}
	return (1);
}

int	copy_str_for_norminette(char *str, char **export, int *i)
{
	export[*i] = ft_strdup(str);
	if (!export[(*i)++])
		return (0);
	return (1);
}

static char	**add_export(char **cmd_splited, char **env,
							int *ret, char **export)
{
	int		i;
	int		k;

	i = 0;
	while (env[i])
	{
		export[i] = ft_strdup(env[i]);
		if (!export[i++])
			return (return_flag(ret));
	}
	k = 0;
	while (cmd_splited[++k])
	{
		if (check_valid(cmd_splited[k], ret, env) == ALL_GOOD)
			if (!copy_str_for_norminette(cmd_splited[k], export, &i))
				return (return_flag(ret));
		if (check_valid(cmd_splited[k], ret, env) == SAME_KEY)
			copy_same_key(cmd_splited[k], export);
	}
	export[i] = NULL;
	return (export);
}

int	all_not_valid(char **cmd_splited, char **env)
{
	int	not_valid;
	int		i;

	i = 1;
	not_valid = 0;
	while (cmd_splited[i])
	{
		if (check_valid(cmd_splited[i], NULL, env) == NOT_VALID)
		{
			not_valid_export("export", cmd_splited[i]);
			not_valid++;
		}
		else if (check_valid(cmd_splited[i], NULL, env) == 2)
			not_valid++;
		i++;
	}
	if (not_valid != (arr_len(cmd_splited) - 1))
		return (1);
	return (0);
}

int	ft_export(char **cmd_splited, char **env, t_minish *minish)
{
	int		ret;
	char	**export;

	if (arr_len(cmd_splited) == 1)
		return (just_export(env));
	if (!all_not_valid(cmd_splited, env))
		return (1);
	export = ft_calloc(sizeof(char *),
			(arr_len(env) + valid_export_len(cmd_splited, env) + 1));
	if (!export)
		return (1);
	ret = 0;
	minish->env = add_export(cmd_splited, env, &ret, export);
	free_arr(env);
	return (ret);
}
