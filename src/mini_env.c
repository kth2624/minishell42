/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:42:09 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/21 15:57:51 by seongjki         ###   ########.fr       */
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
				printf("%s=%s\n", head->key, head->value);
				cnt++;
			}
			head = head->next;
		}
	}
	printf("_=usr/bin/env\n");
	return (0);
}
