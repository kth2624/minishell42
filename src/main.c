/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:13:54 by tkim              #+#    #+#             */
/*   Updated: 2021/12/19 00:35:56 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*split_key_value(char *str)
{
	char	*value;
	char	*key;
	int		idx;
	char	*ptr;
	t_lst	*new;

	ptr = ft_strdup(str);
	idx = 0;
	while (ptr[idx] != '=')
		idx++;
	ptr[idx] = 0;
	key = ptr;
	value = ptr + idx + 1;
	new = mini_lstnew(key, value);
	return (new);
}

int	init_env(t_lst **env_lst, char *envp[])
{
	t_lst	*new;
	int		size;
	int		idx;

	idx = 0;
	while (envp[idx])
		idx++;
	size = idx;
	idx = 0;
	while (idx < size - 1)
	{
		new = split_key_value(envp[idx]);
		mini_lstaddback(env_lst, new);
		idx++;
	}
	return (0);
}

int	minishell(char *envp[])
{
	t_lst	*env_lst;
	char	*input;

	//init_env(&env_lst, envp);
	while (1)
	{
		input = readline("minishell42 $ ");
		if (!input)
			return (0);
		first_parsing(input);
		add_history(input);
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	printf("Hello minishell!\n");
	minishell(envp);
	return 0;
}