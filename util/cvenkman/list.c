/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 00:10:00 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/31 17:29:24 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*msh_lstnew(char *key, char *value, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->str = str;
	new->next = NULL;
	return (new);
}

void	msh_lstadd_back(t_env **lst, t_env *new_list)
{
	t_env	*last;

	last = NULL;
	if (!*lst)
		*lst = new_list;
	else
	{
		last = msh_lstlast(*lst);
		last->next = new_list;
	}
}

t_env	*msh_lstlast(t_env *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}
