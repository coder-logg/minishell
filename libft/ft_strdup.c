/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:43:09 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/20 05:10:57 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*new_str;
	char	*tmp;
	int		i;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	tmp = (char *)str;
	if (!tmp || !new_str)
		return (NULL);
	while (tmp[i])
	{
		new_str[i] = tmp[i];
		// new_str2++;
		// str++;
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
