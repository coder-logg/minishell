#include "../minishell.h"

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
static char *get_env(char *str, char *env_name_dst)
{
	unsigned int	j;

	if (*str == '$')
	{
		j = 0;
		if (ft_isdigit(*(++str)))
			return (NULL);
		while (*str && *str != '\"' && is_env_chr(*str))
			env_name_dst[j++] = *(str++);
		return (getenv(env_name_dst));
	}
	return (NULL);
}

int	read_env(char **str, int pos)
{
	char	*env_val;
	char	env_name[200];

	ft_bzero(env_name, 200);
	env_name[0] = '$';
	env_val = get_env(*str + pos, env_name + 1);
	if (env_val)
	{
		set_free((void **)str, replace_subst(*str, env_name, env_val, 0));
	}
	return (pos + ft_strlen(env_val));
}