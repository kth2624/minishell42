/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:28:20 by tkim              #+#    #+#             */
/*   Updated: 2021/12/20 19:58:07 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **path_parsing(t_lst *env_lst)
{
	char **path_arr;
	char *path;
	int i = 0;
	while(env_lst)
	{
		if (ft_strcmp(env_lst->key, "PATH") == 0)
			path = env_lst->value;
		env_lst = env_lst->next;
	}
	path_arr = ft_split(path, ':');

	return (path_arr);
}