/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:10:37 by tkim              #+#    #+#             */
/*   Updated: 2021/12/22 19:12:59 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_quote_len(char *input, int *idx)
{
	int len;

	len = 0;
	(*idx)++;
	while (input[*idx] && input[*idx] != '\'')
		(*idx)++;
	len++;
	(*idx)++;
	return (len);
}

char *parse_case_quote(char *input, int *i)
{
	int len;
	char *temp;

	len = 0;
	(*i)++;
	while (input[*i + len] && input[*i + len] != '\'')
		len++;
	temp = ft_substr(input, *i, len);
	*i += len + 1;
	return (temp);
}