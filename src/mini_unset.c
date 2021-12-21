/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:20:17 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/21 15:19:26 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_func(t_lst **env_lst, char *key)
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
	return (1);
}

int	mini_unset(t_lst **env_lst, char *argv[])
{
	int	idx;
	int	ret;

	idx = 0;
	while (argv[idx])
	{
		ret = unset_func(env_lst, argv[idx]);
		idx++;
	}
	return (ret);
}
