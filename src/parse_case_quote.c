/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:10:37 by tkim              #+#    #+#             */
/*   Updated: 2021/12/22 18:51:56 by tkim             ###   ########.fr       */
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