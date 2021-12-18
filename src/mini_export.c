/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:20:36 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/18 16:39:31 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_key_value(t_lst *env_lst)
{
	while (env_lst)
	{
		printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}

static void	swap_key_value(t_lst *curr, t_lst *next)
{
	char	*temp_key;
	char	*temp_value;
	int		temp_idx;

	temp_key = curr->key;
	temp_value = curr->value;
	temp_idx = curr->idx;
	curr->key = next->key;
	curr->value = next->value;
	curr->idx = next->idx;
	next->key = temp_key;
	next->value = temp_value;
	next->idx = temp_idx;
}

int	mini_export(t_lst **env_lst, char *str)
{
	t_lst	*curr;
	t_lst	*next;
	int		size;
	t_lst	*new;


	size = mini_lstlen(*env_lst);
	if (!str)
	{
		while (size--)
		{
			curr = *env_lst;
			next = curr->next;
			while (next)
			{
				if (ft_strcmp(curr->key, next->key) > 0)
					swap_key_value(curr, next);
				curr = curr->next;
				next = next->next;
			}
		}
		print_key_value(*env_lst);
	}
	else
	{
		new = split_key_value(str, size);
		mini_lstaddback(env_lst, new);
	}
	return (0);
}
