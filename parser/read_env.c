#include "../minishell.h"

/**
 * @param env string array of environment variables
 * @param key environment variable's name
 * @return index in <b>env</b> that points to string starts with <b>key</b>
 */
int	get_envi(char **env, const char *key)
{
	int	key_len;
	int	i;
	int arr_size;

	i = 0;
	key_len = ft_strlen(key);
	arr_size = arr_len(env);
	if (!ft_strchr(key, '='))
	{
		key = ft_strjoin(key, "=");
		key_len++;
	}
	while (i < arr_size)
	{
		if (ft_strnstr(env[i], key, key_len))
			return (i);
		i++;
	}
	return (-1);
}

static bool is_env_chr(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

/**
 * @brief return environment variable's value
 * @param str should point to symbol '$'
 * @param env_name_dst buffer to environment variable's name
 * @return environment variable's value or <b><i>NULL</i></b> if doesn't
 * exist or if <i><b>str = NULL</b></i>
 */
static char *get_env(char *str, char *env_name_dst, char **env)
{
	int	j;

	if (*str == '$')
	{
		j = 0;
		if (ft_isdigit(*(++str)))
		{
			env_name_dst[j] = *str;
			return (NULL);
		}
		while (*str && *str != '\"' && is_env_chr(*str))
			env_name_dst[j++] = *(str++);
		j = get_envi(env, env_name_dst);
		if (j == -1)
			return (NULL);
		else
		{
			env_name_dst = check_malloc(ft_strjoin(env_name_dst, "="));
			if (!env_name_dst)
				return (NULL);
			set_free((void **)&env_name_dst,
					 replace_subst(env[j], env_name_dst, "", 0));
			return (env_name_dst);
		}
	}
	return (NULL);
}

int read_env(char **str, int pos, char **env)
{
	char	*env_val;
	char	env_name[200];

	ft_bzero(env_name, 200);
	env_name[0] = '$';
	if (!(*str)[pos + 1])
		return (pos + 1);
	if ((*str)[pos + 1] == '?')
	{
		env_name[1] = '?';
		env_val = ft_itoa(g_status);
		set_free((void **)str, replace_subst(*str, env_name, env_val, pos));
		pos += ft_strlen(env_val);
		free(env_val);
		return (pos);
	}
	env_val = get_env(*str + pos, env_name + 1, env);
	if (env_val)
	{
		set_free((void **)str, replace_subst(*str, env_name, env_val, pos));
		return (pos + ft_strlen(env_val));
	}
	else
	{
		set_free((void **)str, replace_subst(*str, env_name, "", pos));
		return (pos + 1);
	}
}