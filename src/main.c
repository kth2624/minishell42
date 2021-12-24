/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:13:54 by tkim              #+#    #+#             */
/*   Updated: 2021/12/24 16:43:42 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(char **str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}

int	exec_func(char **path, char **argv, t_lst **env_lst)
{
	char	**env_arr;

	if (!argv || !path || !env_lst)
		return (0);
	/*if (ft_strcmp(argv[0], "echo") == 0)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			mini_echo(argv, 1);
		else
			mini_echo(argv, 0);
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
		mini_cd(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(argv[0], "unset") == 0)
		mini_unset(env_lst, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		mini_export(env_lst, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		mini_env(*env_lst);*/
	if (exec_built_in_func(argv, env_lst) == 1)
	{
		env_arr = make_env_arr(*env_lst);
		exec_path(path, argv, env_arr);
		free_memory(env_arr);
	}
	free_memory(argv);
	free_memory(path);
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
		init_env_lst(&env_lst, envp);
	while (1)
	{
		input = readline("minishell42 $ ");
		if (!input)
			return (0);
		argv = first_parsing(input, env_lst);
		if (argv)
			path = path_parsing(argv[0], env_lst);
		exec_func(path, argv, &env_lst);
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
	return (0);
}
