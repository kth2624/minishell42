/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:14:03 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/18 14:20:43 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_echo(char *argv[], int flag)
{
	int	idx;

	idx = 1;
	while (argv[idx + 1])
	{
		printf("%s ", argv[idx]);
		idx++;
	}
	printf("%s", argv[idx]);
	if (flag == 1)
		printf("\n");
	return (0);
}
