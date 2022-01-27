/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:57:57 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:50 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_single_quote(char *input, int *idx)
{
	(*idx)++;
	while (input[*idx])
	{
		if (input[*idx] == '\'')
			return (2);
		(*idx)++;
	}
	return (1);
}

int	check_double_quote(char *input, int *idx)
{
	(*idx)++;
	while (input[*idx])
	{
		if (input[*idx] == '"')
			return (2);
		(*idx)++;
	}
	return (1);
}

int	is_valid_quote(char *input)
{
	int	quote;
	int	dquote;
	int	idx;

	quote = 0;
	dquote = 0;
	idx = 0;
	while (input[idx])
	{
		if (input[idx] == '\'')
			quote += check_single_quote(input, &idx);
		else if (input[idx] == '"')
			dquote += check_double_quote(input, &idx);
		idx++;
	}
	if (quote % 2 == 1 || dquote % 2 == 1)
		return (0);
	return (1);
}
