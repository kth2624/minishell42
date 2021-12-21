/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:28:20 by tkim              #+#    #+#             */
/*   Updated: 2021/12/20 20:25:26 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(char *str, char c)
{
	size_t	words;

	words = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			words++;
			str++;
			while (*str && *str != c)
				str++;
		}
	}
	return (words);
}

static void	get_words(char **split, char *str, char c, char *arg)
{
	size_t	i;
	size_t	j;
	size_t	word;
	char *s1;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while (str[i + j] && str[i + j] != c)
				j++;
			s1 = ft_substr(str, i, j);
			split[word] = ft_strjoin(s1, arg);
			free(s1);
			i += j;
			word++;
		}
	}
}

static char	**path_split(char const *s,char *arg, char c)
{
	char	**split;
	int		words;
	char	*str;

	str = (char *)s;
	words = count_words(str, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (0);
	split[words] = 0;
	get_words(split, str, c, arg);
	return (split);
}

char **path_parsing(char *arg, t_lst *env_lst)
{
	char **path_arr;
	char *path;

	while(env_lst)
	{
		if (ft_strcmp(env_lst->key, "PATH") == 0)
			path = env_lst->value;
		env_lst = env_lst->next;
	}
	path_arr = path_split(path, ft_strjoin("/", arg), ':');
	return (path_arr);
}

void	exec_path(char **path_arr, char *argv[])
{
	int	i;
	struct stat	f_stat;
	int	pid;
	int	state;

	i = 0;
	while(path_arr[i])
	{
		if (!stat(path_arr[i], &f_stat))
		{
			pid = fork();
			if (pid > 0)
				wait(&state);
			else if (pid == 0)
				execve(path_arr[i], argv, NULL);
			else if (pid < 0)
				printf("%s\n", strerror(errno));
		}
		i++;
	}
}