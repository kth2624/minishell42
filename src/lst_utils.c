/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:05 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:46 by tkim             ###   ########.fr       */
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

t_token	*mini_tokennew(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->content = content;
	new->type = -1;
	new->next = 0;
	return (new);
}

int	mini_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*head;

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
