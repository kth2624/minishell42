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

char	*mini_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	len;
	size_t	idx;

	idx = 0;
	if (!s1)
	{
		//printf("s2: %s\n", s2);
		ret = ft_strdup(s2);
		return (ret);
	}
	//printf("s1 : %s s2: %s\n", s1, s2);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (*(s1 + idx))
	{
		*(ret + idx) = *(s1 + idx);
		idx++;
	}
	free(s1);
	while (*s2)
		*(ret + idx++) = *s2++;
	*(ret + idx) = '\0';
	return (ret);
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
	temp = 0;
	while (input[i])
	{
		if (is_mini_printable(input[i]))
		{
			temp = mini_strjoin(temp, parse_case_none(input, &i, env_lst));
		}
		if (input[i] == '\'')
		{
			temp =  mini_strjoin(temp, parse_case_quote(input, &i));
		}
		if (input[i] == '"')
		{
			temp = mini_strjoin(temp, parse_case_dquote(input, &i, env_lst));
		}
		if (input[i] == ' ' || input[i] == 0)
		{
			str[j] = ft_strdup(temp);
			free(temp);
			temp = 0;
			j++;
		}
		i++;
	}
	int idx = 0;
	while (str[idx])
		printf("%d : %s\n", idx, str[idx++]);
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
