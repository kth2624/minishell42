/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:13:54 by tkim              #+#    #+#             */
/*   Updated: 2021/12/20 19:57:56 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_built_in_func(char **argv)
{
	if (!argv)
		return (0);
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		mini_echo(argv);
	}
/*
	else if (ft_strcmp(argv[0], "cd")

	else if (ft_strcmp(argv[0], "pwd")

	else if (ft_strcmp(argv[0], "unset")

	else if (ft_strcmp(argv[0], "export")

	else if (ft_strcmp(argv[0], "env")
*/
	else
		printf("error\n");
	return (0);
}

int	minishell(char *envp[])
{
	t_lst	*env_lst;
	char	*input;
	char	**argv;

	env_lst = 0;
	if (!env_lst)
		init_env(&env_lst, envp);
	while (1)
	{
		input = readline("minishell42 $ ");
		if (!input)
			return (0);
		argv = first_parsing(input, env_lst);
		path_parsing(env_lst);
		exec_built_in_func(argv);
		add_history(input);
		free(input);
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	printf("Hello minishell!\n");
	minishell(envp);
	return 0;
}
