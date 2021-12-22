/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_dquote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:10:53 by tkim              #+#    #+#             */
/*   Updated: 2021/12/22 18:53:40 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_dquote_len(char *input, int *idx)
{
	int len;

	len = 0;
	(*idx)++;
	while (input[*idx] && input[*idx] != '"')
		(*idx)++;
	len++;
	(*idx)++;
	return (len);
}