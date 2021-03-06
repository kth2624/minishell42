/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_case_none.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:21 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:35 by tkim             ###   ########.fr       */
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
	while (input[*idx + key_len] && input[*idx + key_len] != ' ' && \
	input[*idx + key_len] != '$' && input[*idx + key_len] != '"' && \
	input[*idx + key_len] != '\'')
		key_len++;
	key = ft_substr(input, *idx, key_len);
	*idx += key_len;
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			len += ft_strlen(env_lst->value);
		env_lst = env_lst->next;
	}
	free(key);
	return (len);
}

static int	cnt_none_len(char *input, int idx, t_lst *env_lst)
{
	int		len;
	int		i;

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
	int		idx;
	char	*env_str;
	int		len;
	int		e_idx;

	idx = 0;
	len = cnt_none_len(input, *i, env_lst);
	while (is_mini_printable(input[*i]) && input[*i])
	{
		if (input[*i] == '$')
		{
			e_idx = 0;
			env_str = parse_case_doller(input, i, env_lst);
			if (!env_str)
				return ;
			while (env_str[e_idx])
				(*str)[idx++] = env_str[e_idx++];
			free(env_str);
		}
		else
			(*str)[idx++] = input[(*i)++];
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
	(*i)--;
	return (temp);
}
