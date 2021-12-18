/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:02:40 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/18 14:21:35 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_lst	*env_lst;

	(void) argc;
	(void) argv;
	init_env(&env_lst, envp);
	printf("size: %d\n", mini_lstlen(env_lst));
	printf("_____________________test_export___________________\n");
	mini_export(&env_lst, 0);
	printf("_____________________test_env______________________\n");
	mini_env(env_lst);
	printf("_____________________test_echo______________________\n");
	mini_echo(argv, 0);
}
