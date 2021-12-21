/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:14:03 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/21 13:40:03 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_echo(char *argv[], int flag)
{
	int	idx;

	if (flag == 0)
	{
		idx = 1;
		while (argv[idx + 1])
		{
			printf("%s ", argv[idx]);
			idx++;
		}
		printf("%s\n", argv[idx]);
	}
	else if (flag == 1)
	{
		idx = 2;
		while (argv[idx + 1])
		{
			printf("%s ", argv[idx]);
			idx++;
		}
		printf("%s", argv[idx]);
	}
	return (0);
}
