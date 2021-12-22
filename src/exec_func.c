/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:06:49 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/22 17:58:46 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_str_arr_len(char *str[])
{
	int	idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

int	exec_path(char **path_arr, char *argv[], char *env_arr[])
{
	int			idx;
	struct stat	f_stat;
	int			pid;
	int			state;
	int			path_arr_len;

	path_arr_len = get_str_arr_len(path_arr);
	idx = 0;
	while (path_arr[idx])
	{
		if (!stat(path_arr[idx], &f_stat))
		{
			pid = fork();
			if (pid > 0)
				wait(&state);
			else if (pid == 0)
				execve(path_arr[idx], argv, env_arr);
			else if (pid < 0)
				printf("%s\n", strerror(errno));
			break ;
		}
		idx++;
	}
	if (idx == path_arr_len)
		printf("minishell42: %s: command not found\n", argv[0]);
	// free(env_arr);
	return (0);
}

int	exec_built_in_func(char *argv[], t_lst **env_lst)
{
	if (ft_strcmp(argv[0], "echo") == 0)
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
		mini_env(*env_lst);
	else
		return (1);
	return (0);
}
