/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:41:16 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/16 16:41:27 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(void)
{
	char	*name;
	char	*err_msg;

	name = 0;
	name = getcwd(name, 0);
	if (name == 0)
	{
		err_msg = strerror(errno);
		printf("%s\n", err_msg);
		return (errno);
	}
	printf("%s\n", name);
	free(name);
	return (0);
}
