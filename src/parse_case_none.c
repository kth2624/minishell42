/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_none.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:12:05 by tkim              #+#    #+#             */
/*   Updated: 2021/12/25 00:20:39 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_mini_printable(char c)
{
	if (' ' <= c && c <= '~')
	{
		if (c == ' ')
			return (0);
		return (1);
	}
	return (0);
}

int	cnt_none_len(char *input, int idx)
{
	int len;
	int	i;

	i = idx;
	len = 0;
	while (input[i] != ' ' && input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char *parse_case_none(char *input, int *i)
{
	int len;
	char *temp;
	int	idx;

	len = cnt_none_len(input, *i);

	temp = (char *)malloc(sizeof(char) * (len + 1));
	idx = 0;
	if (!temp)
		return (0);
	temp[len] = 0;
	while (idx < len)
	{
		if (input[*i] == '\'' || input[*i] == '"')
			(*i)++;
		else
		{
			temp[idx] = input[*i];
			idx++;
			(*i)++;
		}
	}
	printf("temp : %s\n", temp);
	return (temp);
}