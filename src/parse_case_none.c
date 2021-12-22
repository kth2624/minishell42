/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_none.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:12:05 by tkim              #+#    #+#             */
/*   Updated: 2021/12/22 19:43:36 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_mini_printable(char c)
{
	if (' ' <= c && c <= '~')
	{
		if (c == '	' || c == ' ' || c == '\'' || c == '"' || c == '$')
			return (0);
		return (1);
	}
	return (0);
}

int	cnt_none_len(char *input, int *idx)
{
	int len;

	len = 0;
	while (input[*idx] && input[*idx] != ' ' && is_mini_printable(input[*idx]))
		(*idx)++;
	len++;
	return (len);
}

char *parse_case_none(char *input, int *i)
{
	int len;
	char *temp;

	len = 0;
	while (input[*i + len] && input[*i + len] != ' ' && is_mini_printable(input[*i + len]))
		len++;
	temp = ft_substr(input, *i, len);
	*i += len;
	return (temp);
}