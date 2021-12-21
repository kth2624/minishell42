/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:28:51 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/21 17:42:08 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*mini_lstnew(char *key, char *value, int idx)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->idx = idx;
	new->next = 0;
	return (new);
}

int	mini_lstaddback(t_lst **lst, t_lst *new)
{
	t_lst	*head;

	if (!(*lst))
	{
		*lst = new;
		return (0);
	}
	head = *lst;
	while (head->next)
		head = head->next;
	head->next = new;
	return (0);
}

int	mini_lstlen(t_lst *lst)
{
	int	idx;

	idx = 0;
	while (lst)
	{
		idx++;
		lst = lst->next;
	}
	return (idx);
}
