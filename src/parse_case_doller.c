#include "minishell.h"

char	*replace_doller(char *arg, t_lst *env_lst)
{
	char	*ret;

	if (ft_strcmp(arg, "?") == 0)
	{
		return (ft_itoa(g_status));
	}
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, arg) == 0)
		{
			free(arg);
			ret = ft_strdup(env_lst->value);
			return (ret);
		}
		env_lst = env_lst->next;
	}
	free(arg);
	return (ft_strdup(""));
}

int	cnt_doller_len(char *input, int *idx)
{
	int	len;

	len = 0;
	(*idx)++;
	while (input[*idx] && input[*idx] != ' ')
		(*idx)++;
	len++;
	return (len);
}

char	*parse_case_doller(char *input, int *i, t_lst *env_lst)
{
	int		len;
	char	*temp;

	len = 0;
	(*i)++;
	while (input[*i + len] && input[*i + len] != ' ' && \
	input[*i + len] != '$' && input[*i + len] != '"' && input[*i + len] != '\'')
		len++;
	temp = replace_doller(ft_substr(input, *i, len), env_lst);
	*i += len;
	return (temp);
}
