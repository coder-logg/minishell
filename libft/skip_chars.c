#include "libft.h"

char	*skip_chars(const char *str, const char *chars)
{
	if (str == NULL || chars == NULL)
		return (NULL);
	while (*str)
	{
		if (ft_strchr(chars, *(str)) == NULL)
			return ((char *)str);
	}
	return ((char *)str);
}
