/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:13:54 by tkim              #+#    #+#             */
/*   Updated: 2021/12/16 10:20:22 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char *envp[])
{
	char	*input;

	while (1)
	{
		input = readline("minishell $ ");
		if (!input)
			return (0);
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
