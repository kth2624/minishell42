/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:56:36 by tkim              #+#    #+#             */
/*   Updated: 2021/12/20 14:14:03 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 생각해볼것 
 따옴표가 하나만 들어왔을 때 처리 
 또 다른 예외는 없는가 
 함수 어떻게 나눌지
 abc"abc"'abc' 같은 경우 처리함
 (argv {'abc' ' ' 'abc' ' ' 'abc' 0})
 이런식으로 만듬
*/
int	is_mini_printable(char c)
{
	if (' ' <= c && c <= '~')
	{
		if (c == '	' || c == ' ' || c == '\'' || c == '"')
			return (0);
		return (1);
	}
	return (0);
}
/*
int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}
*/
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
			while (input[i] && input[i] != ' ' && is_mini_printable(input[i]))
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
			while (input[i] && input[i] != '"')
				i++;
			word_len++;
			i++;
		}
		else if (input[i] == ' ')
		{
			word_len++;
			while (input[i] == ' ')
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
	//printf("cnt = %d\n", cnt);
	str = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!str)
		return (0);
	i = 0;
	j = 0;
	str[cnt] = 0;
	while (input[i])
	{
		len = 0;
		
		if (is_mini_printable(input[i]))
		{
			while (input[i + len] && input[i + len] != ' ' && is_mini_printable(input[i + len]))
				len++;
			str[j] = ft_substr(input, i, len);
			//printf("mini %s\n", str[j]);
			j++;
			i += len;
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i + len] && input[i + len] != '\'')
				len++;
			str[j] = ft_substr(input, i, len);
			//printf("mini %s\n", str[j]);
			j++;
			i += len + 1;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i + len] && input[i + len] != '\"')
				len++;
			str[j] = ft_substr(input, i, len);
			//printf("mini %s\n", str[j]);
			j++;
			i += len + 1;
		}
		else if (input[i] == ' ')
		{
			str[j] = ft_strdup(" ");
			//printf("mini %s\n", str[j]);
			while (input[i] == ' ')
				i++;
			j++;
		}
		else
			i++;
	}
	return (str);
}

char *first_parsing(char *input)
{
	char **str;

	if (!input[0])
		return (0);
	str = make_str_arr(input);
	return (str);
}
