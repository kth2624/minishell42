/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:15 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:39 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_key_value(t_lst *env_lst)
{
	while (env_lst)
	{
		printf("declare -x ");
		printf("%s", env_lst->key);
		if (ft_strcmp(env_lst->value, "") == 0)
			printf("\n");
		else
			printf("=\"%s\"\n", env_lst->value);
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
	t_lst	*head;
	int		size;

	head = *env_lst;
	size = mini_lstlen(*env_lst);
	new = split_key_value(str, size);
	while (head)
	{
		if (ft_strcmp(head->key, new->key) == 0)
		{
			free(head->key);
			free(head->value);
			head->key = ft_strdup(new->key);
			head->value = ft_strdup(new->value);
			free(new->key);
			free(new->value);
			free(new);
			return (0);
		}
		head = head->next;
	}
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
