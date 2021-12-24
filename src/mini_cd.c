/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:40:53 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/24 15:08:07 by tkim             ###   ########.fr       */
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
		printf("minishell42: cd: ");
		err_msg = strerror(errno);
		printf("%s: ", path);
		printf("%s\n", err_msg);
		return (1);
	}
	return (0);
}
