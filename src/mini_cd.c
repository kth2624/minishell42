/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:40:53 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/21 14:50:05 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(char *argv[])
{
	char	*err_msg;
	char	*path;

	path = argv[1];
	if (chdir(path) == -1)
	{
		printf("cd: ");
		err_msg = strerror(errno);
		printf("%s: ", err_msg);
		printf("%s\n", path);
		return (1);
	}
	return (0);
}
