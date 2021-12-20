/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:44:58 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/20 12:11:16 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*split_key_value(char *str, int lst_idx)
{
	char	*value;
	char	*key;
	int		idx;
	t_lst	*new;

	idx = 0;
	while (str[idx] != '=')
		idx++;
	str[idx] = 0;
	key = str;
	value = str + idx + 1;
	new = mini_lstnew(key, value, lst_idx);
	return (new);
}

int	init_env(t_lst **env_lst, char *envp[])
{
	t_lst	*new;
	int		size;
	int		idx;

	idx = 0;
	while (envp[idx])
		idx++;
	size = idx;
	idx = 0;
	while (idx < size - 1)
	{
		new = split_key_value(envp[idx], idx);
		mini_lstaddback(env_lst, new);
		idx++;
	}
	return (0);
}
