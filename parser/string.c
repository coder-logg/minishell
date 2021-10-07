#include "../minishell.h"

/**
 * replace substring in string
 * @param str string to search substring
 * @param substr string which will be replaced if found
 * @param replacement string to replacement
 * @return new string in which first found <b><i>substr</i></b> will be
 * replaced with <b><i>replacement</i></b> or <b><i>NULL</i></b> if wasn't found
 */
char	*replace_subst(char *str, char *substr, char *replacement)
{
	char	*res;
	char	*place;
	int		len;

	len = ft_strlen(str) - ft_strlen(substr) + ft_strlen(replacement);
	res = ft_calloc(len + 1, sizeof(char));
	place = ft_strstr(str, substr);
	if (place == NULL)
		return (NULL);
	len = place - str;
	ft_strlcpy(res, str, len + 1);
	ft_strcpy(res + len, replacement);
	ft_strcpy(res + len + ft_strlen(replacement), place + ft_strlen(substr));
	return (res);
}