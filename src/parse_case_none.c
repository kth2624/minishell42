/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_none.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:12:05 by tkim              #+#    #+#             */
/*   Updated: 2021/12/25 00:20:39 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_mini_printable(char c)
{
	if (' ' <= c && c <= '~')
	{
		if (c == ' ' || c == '\'' || c == '"')
			return (0);
		return (1);
	}
	return (0);
}

static int	get_env_str_len(char *input, int *idx, t_lst *env_lst)
{
	int		key_len;
	char	*key;
	int		len;

	key_len = 0;
	len = 0;
	while (input[*idx + key_len] && input[*idx + key_len] != ' ' && input[*idx + key_len] != '$')
		key_len++;
	key = ft_substr(input, *idx, key_len);
	*idx += key_len;
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			len += ft_strlen(env_lst->value);
		env_lst = env_lst->next;
	}
	return (len);
}

static int	cnt_none_len(char *input, int idx, t_lst *env_lst)
{
	int		len;
	int		i;
	char	*key;
	int		key_len;

	i = idx;
	len = 0;
	while (is_mini_printable(input[i]) && input[i])
	{
		if (input[i] == '$')
			{
				i++;
				len += get_env_str_len(input, &i, env_lst);
			}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	fill_str(char *input, int *i, t_lst *env_lst, char **str)
{
	int	idx;
	char	*env_str;
	int	len;

	idx = 0;
	len = cnt_none_len(input, *i, env_lst);
	while (idx < len)
	{
		if (input[*i] == '$')
		{
			env_str = parse_case_doller(input, i, env_lst);
			while (*env_str)
				(*str)[idx++] = *env_str++;
		}
		else
		{
			(*str)[idx] = input[*i];
			idx++;
			(*i)++;
		}
	}
}

char	*parse_case_none(char *input, int *i, t_lst *env_lst)
{
	int		len;
	char	*temp;
	int		idx;

	len = cnt_none_len(input, *i, env_lst);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	idx = 0;
	temp[len] = 0;
	fill_str(input, i, env_lst, &temp);
	//printf("temp : %s\n", temp);
	return (temp);
}