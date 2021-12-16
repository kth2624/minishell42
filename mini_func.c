/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:20:36 by seongjki          #+#    #+#             */
/*   Updated: 2021/12/16 12:44:51 by seongjki         ###   ########.fr       */
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

int	mini_cd(const char *path)
{
	char	*err_msg;

	if (chdir(path) == -1)
	{
		err_msg = strerror(errno);
		printf("%s\n", err_msg);
		return (errno);
	}
	return (0);
}

int	mini_env(char *envp[])
{
	int	idx;

	idx = 0;
	while (envp[idx])
	{
		printf("%s\n", envp[idx]);
		idx++;
	}
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	mini_pwd();
	printf("exec cd...\n");
	mini_cd("..");
	mini_pwd();
	mini_env(envp);
}
