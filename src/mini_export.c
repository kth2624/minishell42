/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:20:36 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/21 17:32:43 by seongjki         ###   ########.fr       */
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

static int	export_print_func(t_lst **env_lst)
{
	t_lst	*curr;
	t_lst	*next;
	int		size;

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
	return (0);
}

int	export_add_func(t_lst **env_lst, char *str)
{
	t_lst	*new;
	int		size;

	size = mini_lstlen(*env_lst);
	new = split_key_value(str, size);
	mini_lstaddback(env_lst, new);
	return (0);
}

int	mini_export(t_lst **env_lst, char *argv[])
{
	int	idx;
	int	ret;

	ret = 0;
	idx = 1;
	if (!argv[idx])
		ret = export_print_func(env_lst);
	else
	{
		while (argv[idx])
		{
			ret = export_add_func(env_lst, argv[idx]);
			idx++;
		}
	}
	return (ret);
}
