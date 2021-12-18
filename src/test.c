/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:02:40 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/19 00:37:49 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_lst	*env_lst;

	(void) argc;
	(void) argv;
	init_env(&env_lst, envp);
	mini_cd("libft");
	mini_export(&env_lst, "a=3");
	mini_export(&env_lst, "A=3");
	mini_export(&env_lst, 0);
	mini_unset(&env_lst, "a");
	mini_export(&env_lst, 0);
}
