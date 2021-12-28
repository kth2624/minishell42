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

static int	get_env_str_len(char *input, int *idx, t_lst *env_lst)
{
	int		key_len;
	char	*key;
	int		len;

	key_len = 0;
	len = 0;
	while (input[*idx + key_len] && input[*idx + key_len] != ' ' && input[*idx + key_len] != '$' && input[*idx + key_len] != '"' && \
	input[*idx + key_len] != '\'')
		key_len++;
	//printf("key_len : %d\n", key_len);
	key = ft_substr(input, *idx, key_len);
	//printf("key :  %s\n", key);
	*idx += key_len;
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			len += ft_strlen(env_lst->value);
		env_lst = env_lst->next;
	}
	return (len);
}

static int	cnt_dquote_len(char *input, int idx, t_lst *env_lst)
{
	int		len;
	int		i;
	char	*key;
	int		key_len;

	i = idx;
	len = 0;
	while (input[i] != '"' && input[i])
	{
		//printf("input[i] : '%c'\n", input[i]);
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
	len = cnt_dquote_len(input, *i, env_lst);
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

char	*parse_case_dquote(char *input, int *i, t_lst *env_lst)
{
	int		len;
	char	*temp;

	(*i)++;
	len = cnt_dquote_len(input, *i, env_lst);
	//printf("dqlen : %d\n", len);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	temp[len] = 0;
	fill_str(input, i, env_lst, &temp);
	printf("dquote : %s\n", temp);
	printf("input[i] : '%c'\n", input[*i]);
	return (temp);
}