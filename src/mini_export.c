/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:20:36 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/16 18:13:26 by seongjki         ###   ########.fr       */
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

	temp_key = curr->key;
	temp_value = curr->value;
	curr->key = next->key;
	curr->value = next->value;
	next->key = temp_key;
	next->value = temp_value;
}

int	mini_export(t_lst **env_lst, char *str)
{
	t_lst	*curr;
	t_lst	*next;
	int		size;
	t_lst	*new;

	if (!str)
	{
		size = mini_lstlen(*env_lst);
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
		new = split_key_value(str);
		mini_lstaddback(env_lst, new);
	}
	return (0);
}
