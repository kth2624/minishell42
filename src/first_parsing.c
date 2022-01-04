
#include "minishell.h"

int	cnt_word(char *input, int i)
{
	int	word_len;
	printf("hi \n");
	if (!input)
		return (0);
	word_len = 0;
	while (input[i])
	{
		printf("c = %c i = %d\n", input[i], i);
		while (input[i] == ' ')
			i++;
		if (is_mini_printable(input[i]))
		{
			while (is_mini_printable(input[i]))
			{
				printf("c = %c i = %d\n", input[i], i);
				i++;
			}
		}
		else if(input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (input[i] == '|')
				i++;
			while (input[i] == '<')
				i++;
			while (input[i] == '>')
				i++;
		}
		/*
		else if(input[i] == '\'')
		{
			i++;
			while(input[i] != '\'')
				i++;
			i++;

		}else if(input[i] == '"')
		{
			i++;
			while(input[i] != '"')
				i++;
			i++;

		}*/

		word_len++;
	printf("word=%d, i=%d\n",word_len,i);
	}
	return (word_len);
}

char **malloc_str(char *input)
{
	int cnt;
	char **str;

	cnt = cnt_word(input, 0);
	//str = (char **)malloc(sizeof(char *) * (cnt + 1));
	//if (!str)
	//	return (0);
	//str[cnt] = 0;
	return (str);
}

char	*mini_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		len;
	int		idx;
	int		r_idx;

	idx = 0;
	r_idx = 0;
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
	while (s1[idx])
	{
		ret[r_idx] = s1[idx];
		idx++;
		r_idx++;
	}
	free(s1);
	idx = 0;
	while (s2[idx])
	{
		ret[r_idx] = s2[idx];
		r_idx++;
		idx++;
	}
	free(s2);
	ret[r_idx] = '\0';
	return (ret);
}

char	**make_str_arr(char *input, t_lst *env_lst)
{
	char	**str;
	int		i;
	int		j;
	char	*temp;

	str = malloc_str(input);
	// i = 0;
	// j = 0;
	// temp = 0;
	// while (input[i])
	// {
	// 	if (input[i] != '\'' && input[i] != '"' && input[i] != ' ')
	// 		temp = mini_strjoin(temp, parse_case_none(input, &i, env_lst));
	// 	else if (input[i] == '\'')
	// 		temp = mini_strjoin(temp, parse_case_quote(input, &i));
	// 	else if (input[i] == '"')
	// 		temp = mini_strjoin(temp, parse_case_dquote(input, &i, env_lst));
	// 	i++;
	// 	if (input[i] == ' ' || input[i] == 0)
	// 	{
	// 		while (input[i] == ' ' && input[i])
	// 			i++;
	// 		if (temp)
	// 		{
	// 			str[j] = ft_strdup(temp);
	// 			free(temp);
	// 			temp = 0;
	// 			j++;
	// 		}
	// 	}
	// }
	return (str);
}

char **first_parsing(char *input, t_lst *env_lst)
{
	char **str;

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
