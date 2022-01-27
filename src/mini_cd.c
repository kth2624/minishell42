/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:11 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:42 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_old_pwd_val(t_lst *env_lst, char *old_pwd)
{
	t_lst	*head;

	head = env_lst;
	while (head)
	{
		if (ft_strcmp(head->key, "OLDPWD") == 0)
		{
			free(head->value);
			head->value = old_pwd;
			return ;
		}
		head = head->next;
	}
}

static void	init_pwd_val(t_lst *env_lst)
{
	char	*pwd;
	char	*old_pwd;
	t_lst	*head;

	head = env_lst;
	pwd = 0;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return ;
	while (head)
	{
		if (ft_strcmp(head->key, "PWD") == 0 && ft_strcmp(pwd, head->key) != 0)
		{
			old_pwd = ft_strdup(head->value);
			free(head->value);
			head->value = pwd;
			init_old_pwd_val(env_lst, old_pwd);
		}
		head = head->next;
	}
}

char	*set_home_path(t_lst *env_lst)
{
	t_lst	*head;

	head = env_lst;
	while (head)
	{
		if (ft_strcmp(head->key, "HOME") == 0)
			return (head->value);
		head = head->next;
	}
	return (0);
}

int	mini_cd(char *argv[], t_lst *env_lst)
{
	char	*err_msg;
	char	*path;

	path = argv[1];
	if (!path || ft_strcmp(path, "~") == 0)
	{
		free(path);
		path = set_home_path(env_lst);
	}
	if (!path)
	{
		free(path);
		write(2, "minishell42: cd: HOME not set\n", 31);
		return (1);
	}
	if (chdir(path) == -1)
	{
		printf("minishell42: cd: ");
		err_msg = strerror(errno);
		printf("%s: ", path);
		printf("%s\n", err_msg);
		return (1);
	}
	init_pwd_val(env_lst);
	return (0);
}
