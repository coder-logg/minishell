/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:21:52 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/02 04:24:57 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	not_valid_export(char *cmd, char *str)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "'", 1);
	write(2, ": ", 2);
	write(2, "not a valid identifier\n", 24);
}

static int check_same_key(char *str, char **env)
{
	int	i;
	int	key_len;
	int	env_key_len;

	i = 0;
	key_len = 0;
	while (str[key_len] != '\0' && str[key_len] != '=')
		key_len++;
	while (env[i])
	{
		if (!ft_strcmp(str, env[i]))
			return (2);
		env_key_len = 0;
		while (env[i][env_key_len] != '\0' && env[i][env_key_len] != '=')
			env_key_len++;
		if (env_key_len == key_len)
			if (!ft_strncmp(str, env[i], key_len))
				return (SAME_KEY);
		i++;
	}
	return (ALL_GOOD);
}

int	check_valid(char *str, int *ret, char **env)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (NOT_VALID);
	if (!ft_strncmp(str, "_=", 2))
		return (2);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
		{
			if (ret != NULL)
				*ret = 1;
			return (NOT_VALID);
		}
		i++;
	}
	return (check_same_key(str, env));
}

int	valid_export_len(char **cmd_splited, char **env)
{
	int		i;
	int		valid_export;

	i = 1;
	valid_export = 0;
	while (cmd_splited[i])
	{
		if (check_valid(cmd_splited[i], NULL, env) == ALL_GOOD)
			valid_export++;
		i++;
	}
	return (valid_export);
}

void	*return_flag(int *ret)
{
	*ret = 1;
	return (NULL);
}
