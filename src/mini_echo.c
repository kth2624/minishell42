/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:14:03 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/20 14:11:24 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	idx;

	idx = 2;
	while (argv[idx])
	{
		printf("%s", argv[idx]);
		idx++;
	}
	printf("\n");
	return (0);
}
