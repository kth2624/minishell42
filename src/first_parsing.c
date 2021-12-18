/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:56:36 by tkim              #+#    #+#             */
/*   Updated: 2021/12/19 02:01:59 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_mini_printable(char c)
{
	if (' ' <= c && c <= '~')
	{
		if (c == 9 || c == 39 || c == 34 || c == 32)
			return (0);
		return (1);
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

int	cnt_word(char *input)
{
	int	word_len;
	int	i;

	word_len = 0;
	i = 0;
	while (input[i])
	{
		if (is_mini_printable(input[i]))
		{
			while (input[i] && input[i] != ' ')
				i++;
			word_len++;
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			word_len++;
			i++;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				i++;
			word_len++;
			i++;
		}
		else
			i++;
	}
	return (word_len);
}

char	**make_str_arr(char *input)
{
	int		cnt;
	char	**str;
	int		i;
	int		j;
	int		len;

	cnt = cnt_word(input);
	printf("cnt = %d\n", cnt);
	str = (char **)malloc(sizeof(char *) * cnt + 1);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (input[i])
	{
		len = 0;
		if (is_mini_printable(input[i]))
		{
			while (input[i + len] && input[i + len] != ' ')
				len++;
			str[j] = ft_substr(input, i, len);
			printf("mini %s\n", str[j]);
			j++;
			i += len + 1;
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i + len] && input[i + len] != '\'')
				len++;
			str[j] = ft_substr(input, i, len);
			printf("mini %s\n", str[j]);
			j++;
			i += len + 1;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i + len] && input[i + len] != '\"')
				len++;
			str[j] = ft_substr(input, i, len);
			printf("mini %s len = %d\n", str[j], len);
			j++;
			i += len + 1;
		}
		else
			i++;
	}
	return (str);
}

char *first_parsing(char *input)
{
	char **str;

	make_str_arr(input);
	// while (*input)
	// {
	// 	if (is_mini_printable)
	// 	input++;
	// }

	return 0;
}