/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:40:53 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/16 17:58:36 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(const char *path)
{
	char	*err_msg;

	if (chdir(path) == -1)
	{
		printf("cd: ");
		err_msg = strerror(errno);
		printf("%s: ", err_msg);
		printf("%s\n", path);
		return (errno);
	}
	return (0);
}
