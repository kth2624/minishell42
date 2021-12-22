/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:14:03 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/22 17:01:11 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_echo(char *argv[], int flag)
{
	int	idx;

	if (flag == 0)
	{
		idx = 1;
		while (argv[idx])
		{
			printf("%s", argv[idx]);
			if (argv[idx] != 0)
				printf(" ");
			idx++;
		}
		printf("\n");
	}
	else if (flag == 1)
	{
		idx = 2;
		if (!argv[idx])
		 	return (1);
		while (argv[idx + 1])
		{
			printf("%s ", argv[idx]);
			idx++;
		}
		printf("%s", argv[idx]);
	}
	return (0);
}
