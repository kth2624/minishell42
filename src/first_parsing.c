/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:56:36 by tkim              #+#    #+#             */
/*   Updated: 2021/12/25 00:17:37 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_word(char *input)
{
	int	word_len;
	int	i;

	if (!input)
		return (0);
	word_len = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				i++;
			i++;
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
			i++;
		}
		else if (input[i] == ' ')
		{
			while (input[i] == ' ')
				i++;
			word_len++;
		}
		else
			i++;
	}
	return (word_len);
}

char **malloc_str(char *input)
{
	int cnt;
	char **str;

	cnt = cnt_word(input);
	str = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!str)
		return (0);
	str[cnt] = 0;
	return (str);
}

char	**make_str_arr(char *input, t_lst *env_lst)
{
	char	**str;
	int		i;
	int		j;
	int		len;
	char *temp;
	char *temp2;

	str = malloc_str(input);
	i = 0;
	j = 0;

	len = 0;
	while (input[i])
	{
		if (is_mini_printable(input[i]))
		{
			printf("input : %c\n", input[i]);
			str[j] = parse_case_none(input, &i);
			j++;
		}
		i++;
	}
	return (str);
}

char **first_parsing(char *input, t_lst *env_lst)
{
	char **str;
	int	cnt;

	if (!input[0])
		return (0);
	if (!is_valid_quote(input))
	{
		printf("quote error\n");
		return 0;
	}
	str = make_str_arr(input, env_lst);
	return (str);
}
