/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:16 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:38 by tkim             ###   ########.fr       */
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
