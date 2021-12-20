/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:13:54 by tkim              #+#    #+#             */
/*   Updated: 2021/12/20 20:31:47 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_func(char **path, char **argv)
{
	if (!argv || !path)
		return (0);
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		mini_echo(argv);
	}
	else
		exec_path(path, argv);

/*
	else if (ft_strcmp(argv[0], "cd")

	else if (ft_strcmp(argv[0], "pwd")

	else if (ft_strcmp(argv[0], "unset")

	else if (ft_strcmp(argv[0], "export")

	else if (ft_strcmp(argv[0], "env")
*/

	return (0);
}

int	minishell(char *envp[])
{
	t_lst	*env_lst;
	char	*input;
	char	**argv;
	char	**path;

	env_lst = 0;
	if (!env_lst)
		init_env(&env_lst, envp);
	while (1)
	{
		input = readline("minishell42 $ ");
		if (!input)
			return (0);
		argv = first_parsing(input, env_lst);
		path = path_parsing(argv[0], env_lst);
		exec_func(path, argv);
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
