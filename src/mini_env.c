/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:13 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:40 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_lst *env_lst)
{
	t_lst	*head;
	int		size;
	int		cnt;

	size = mini_lstlen(env_lst);
	cnt = 0;
	while (cnt < size)
	{
		head = env_lst;
		while (head)
		{
			if (head->idx == cnt)
			{
				if (ft_strcmp(head->value, "") != 0)
					printf("%s=%s\n", head->key, head->value);
				cnt++;
			}
			head = head->next;
		}
	}
	return (0);
}
