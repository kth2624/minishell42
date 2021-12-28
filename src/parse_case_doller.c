/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_doller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:11:36 by tkim              #+#    #+#             */
/*   Updated: 2021/12/24 14:52:25 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *replace_doller(char *arg, t_lst *env_lst)
{
	//printf("arg = %s\n", arg);
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, arg) == 0)
		{
			//printf("value = %s\n",env_lst->value);
			free(arg);
			return (ft_strdup(env_lst->value));
		}
		env_lst = env_lst->next;
	}
	free(arg);
	return (0);
}

int	cnt_doller_len(char *input, int *idx)
{
	int len;

	len = 0;
	(*idx)++;
	while (input[*idx] && input[*idx] != ' ')
		(*idx)++;
	len++;
	return (len);
}

char *parse_case_doller(char *input, int *i, t_lst *env_lst)
{
	int len;
	char *temp;

	len = 0;
	(*i)++;
	while (input[*i + len] && input[*i + len] != ' ' && input[*i + len] != '$' && input[*i + len] != '"' && \
	input[*i + len] != '\'')
		len++;
	temp = replace_doller(ft_substr(input, *i, len), env_lst);
	*i += len;
	//printf("doller = %c", input[*i]);
	return (temp);
}