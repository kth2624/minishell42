/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:28:51 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/18 14:01:37 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*mini_lstnew(char *key, char *value, int idx)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->idx = idx;
	new->next = 0;
	return (new);
}

int		mini_lstaddback(t_lst **lst, t_lst *new)
{
	t_lst	*head;

	head = *lst;
	if (!head)
	{
		*lst = new;
		return (0);
	}
	while (head->next != 0)
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
