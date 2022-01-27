/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:57:59 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:48 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*first_parsing(char *input, t_lst *env_lst)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!input[0] || !ft_isprint(input[0]))
		return (0);
	if (!is_valid_quote(input))
	{
		printf("quote error\n");
		return (0);
	}
	tokens = 0;
	tokens = tokenize(input);
	convert_content(&tokens, env_lst);
	fill_token_type(tokens);
	cmd = make_cmd(tokens);
	free_token(tokens);
	return (cmd);
}
