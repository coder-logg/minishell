#include "libft.h"

int	str_only_chr(char *s, char *chrs)
{
	while (*s)
	{
		if (ft_strchr(chrs, *s) == NULL)
			return (0);
		s++;
	}
	return (1);
}
