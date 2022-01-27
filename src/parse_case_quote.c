/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:22 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:35 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_case_quote(char *input, int *i)
{
	int		len;
	char	*temp;

	len = 0;
	(*i)++;
	while (input[*i + len] && input[*i + len] != '\'')
		len++;
	temp = ft_substr(input, *i, len);
	*i += len;
	return (temp);
}
