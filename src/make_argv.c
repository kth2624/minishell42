/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:58:07 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:58:44 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mini_strjoin(char *s1, char *s2, int idx, int r_idx)
{
	char	*ret;
	int		len;

	if (!s1)
	{
		ret = ft_strdup(s2);
		free(s2);
		return (ret);
	}
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ret[len] = 0;
	while (s1[idx])
		ret[r_idx++] = s1[idx++];
	free(s1);
	idx = 0;
	while (s2[idx])
		ret[r_idx++] = s2[idx++];
	free(s2);
	return (ret);
}

static int	get_argv_len(t_token *token)
{
	t_token	*head;
	int		len;

	head = token;
	len = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
			len++;
		head = head->next;
	}
	return (len);
}

static char	**alloc_argv_memory(int len)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (0);
	argv[len] = 0;
	return (argv);
}

static void	fill_argv(t_token *token, char **str)
{
	char	**argv;
	t_token	*head;
	int		idx;

	argv = str;
	head = token;
	idx = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == WORD)
		{
			argv[idx] = ft_strdup(head->content);
			idx++;
		}
		head = head->next;
	}
}

char	**make_argv(t_token *token)
{
	char	**argv;
	int		len;

	if (!token)
		return (0);
	len = get_argv_len(token);
	argv = alloc_argv_memory(len);
	fill_argv(token, argv);
	return (argv);
}
