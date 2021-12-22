/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:56:36 by tkim              #+#    #+#             */
/*   Updated: 2021/12/22 18:57:36 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	cnt_word(char *input)
{
	int	word_len;
	int	i;

	word_len = 0;
	i = 0;
	while (input[i])
	{
		if (is_mini_printable(input[i]))
			word_len += cnt_none_len(input, &i);
		else if (input[i] == '\'')
			word_len += cnt_quote_len(input, &i);
		else if (input[i] == '"')
			word_len += cnt_dquote_len(input, &i);
		else if (input[i] == '$')
			word_len += cnt_doller_len(input, &i);
		else
			i++;
	}
	return (word_len);
}



char	**make_str_arr(char *input, t_lst *env_lst)
{
	int		cnt;
	char	**str;
	int		i;
	int		j;
	int		len;
	char *temp;
	char *temp2;

	cnt = cnt_word(input);
//	printf("cnt = %d\n", cnt);
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
		//	printf("mini %s\n", str[j]);
			j++;
			i += len;
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i + len] && input[i + len] != '\'')
				len++;
			str[j] = ft_substr(input, i, len);
		//	printf("mini %s\n", str[j]);
			j++;
			i += len + 1;
		}
		else if (input[i] == '"')
		{
			i++;
			if (input[i] == '$')
			{
				i++;
				while (input[i + len] && input[i + len] != ' ')
					len++;
				temp2 = replace_doller(ft_substr(input, i, len), env_lst);
				i += len;
				while (input[i + len] && input[i + len] != '"')
					len++;
				temp = ft_substr(input, i, len);
				str[j] = ft_strjoin(temp2, temp);
				free(temp);
				free(temp2);
			//	printf("first=%s temp=%s\n",str[j], temp );
				i += len + 1;
			}
			else
			{
				while (input[i + len] && input[i + len] != '"')
					len++;
				str[j] = ft_substr(input, i, len);
			//	printf("mini=%s\n", str[j]);
				j++;
				i += len + 1;
			}
		}
/*
		else if (input[i] == ' ')
		{
			str[j] = ft_strdup(" ");
			//printf("mini %s\n", str[j]);
			while (input[i] == ' ')
				i++;
			j++;
		}
*/
		else if (input[i] == '$')
		{
			i++;
			while (input[i + len] && input[i + len] != ' ')
				len++;
			str[j] = replace_doller(ft_substr(input, i, len), env_lst);
			printf("first = %s\n",str[j]);
			j++;
			i += len + 1;
		}
		else
			i++;
	}
	return (str);
}

char **first_parsing(char *input, t_lst *env_lst)
{
	char **str;

	if (!input[0])
		return (0);
	str = make_str_arr(input, env_lst);
	return (str);
}
