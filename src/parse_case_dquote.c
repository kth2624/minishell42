/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_dquote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:10:53 by tkim              #+#    #+#             */
/*   Updated: 2021/12/22 19:21:12 by tkim             ###   ########.fr       */
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

// char *parse_case_dquote(char *input, int *i)
// {
// 	i++;
// 	if (input[i] == '$')
// 	{
// 		i++;
// 		while (input[i + len] && input[i + len] != ' ')
// 			len++;
// 		temp2 = replace_doller(ft_substr(input, i, len), env_lst);
// 		i += len;
// 		while (input[i + len] && input[i + len] != '"')
// 			len++;
// 		temp = ft_substr(input, i, len);
// 		str[j] = ft_strjoin(temp2, temp);
// 		free(temp);
// 		free(temp2);
// 	//	printf("first=%s temp=%s\n",str[j], temp );
// 		i += len + 1;
// 	}
// 	else
// 	{
// 		while (input[i + len] && input[i + len] != '"')
// 			len++;
// 		str[j] = ft_substr(input, i, len);
// 	//	printf("mini=%s\n", str[j]);
// 		j++;
// 		i += len + 1;
// 	}
// }