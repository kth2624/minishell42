/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:20:17 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/18 14:13:40 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_unset(t_lst **env_lst, char *key)
{
	t_lst	*curr;
	t_lst	*next;

	curr = *env_lst;
	next = curr->next;
	if (ft_strcmp(curr->key, key) == 0)
	{
		*env_lst = next;
		free(curr);
		return (0);
	}
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			next = curr->next->next;
			free(curr->next);
			curr->next = next;
			return (0);
		}
		curr = curr->next;
	}
	return (0);
}
