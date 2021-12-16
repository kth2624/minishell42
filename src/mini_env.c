/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:42:09 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/16 16:43:18 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(char *envp[])
{
	int	idx;
	int	size;

	idx = 0;
	while (envp[idx])
		idx++;
	size = idx;
	idx = 0;
	while (idx < size - 1)
	{
		printf("%s\n", envp[idx]);
		idx++;
	}
	printf("_=usr/bin/env\n");
	return (0);
}
