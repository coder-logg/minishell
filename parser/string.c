#include "../minishell.h"

/**
 * Replace first occurrence substring <b><i>substr</i></b>
 * in string <b><i>str</i></b>
 * @param str string to search substring
 * @param substr string which will be replaced if found
 * @param replacement string to replacement
 * @param pos position in <b><i>str</i></b> from which to search
 * <b><i>substr</i></b>
 * @return new string in which first found <b><i>substr</i></b> will be
 * replaced with <b><i>replacement</i></b> or <b><i>str</i></b> if wasn't found
 */
char	*replace_subst(char *str, char *substr, char *replacement, int pos)
{
	char	*res;
	char	*place;
	int		len;

	place = ft_strstr(str + pos, substr);
	if (place == NULL)
		return (str);
	len = ft_strlen(str) - ft_strlen(substr) + ft_strlen(replacement);
	res = check_malloc(ft_calloc(len + 1, sizeof(char)));
	len = place - str;
	ft_strlcpy(res, str, len + 1);
	ft_strcpy(res + len, replacement);
	ft_strcpy(res + len + ft_strlen(replacement), place + ft_strlen(substr));
	return (res);
}

/**
 * Shrink few repeating characters to a single character.
 * Example: "aaaa" -> "a".
 * @param str string to change
 * @param pos position with symbols to replace
 * @param ch symbol to collapse
 * @return string without repeating characters <b><i>ch</i></b>
 * in this position in string or <b><i>str</i></b> if there isn't
 * repeating characters
 */
char	*shrink_chs_one(char *str, int pos, char ch)
{
	int		i;
	char	*to_collapse;
	char	*res;
	char	ch_str[2];

	i = 0;
	ch_str[0] = ch;
	ch_str[1] = '\0';
	while (str[pos + i] == ch)
		i++;
	if (i == 0 || i == 1)
		return (str);
	to_collapse = check_malloc(ft_calloc(i + 1, sizeof(char)));
	ft_strlcpy(to_collapse, str + pos, i + 1);
	res = replace_subst(str, ch_str, to_collapse, pos);
	free(to_collapse);
	return (res);
}

/**
 * counts number of occurrences of character <b><i>ch</i></b>
 * in string <b><i>str</i></b>
 */
int count_symbol_occur(char *str, char ch)
{
	int counter;

	counter = 0;
	while (*(str))
	{
		if (*str++ == ch)
			counter++;
	}
	return(counter);
}