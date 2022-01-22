#include "minishell.h"

t_lst	*split_key_value(char *str, int lst_idx)
{
	char	*value;
	char	*key;
	int		idx;
	t_lst	*new;

	idx = 0;
	while (str[idx] && str[idx] != '=')
		idx++;
	if (str[idx] == 0)
	{
		key = str;
		value = ft_strdup("");
	}
	else
	{
		str[idx] = 0;
		key = str;
		value = str + idx + 1;
	}
	new = mini_lstnew(key, value, lst_idx);
	return (new);
}

char	**make_env_arr(t_lst *env_lst)
{
	char	**env_arr;
	int		size;
	char	*elem;
	char	*temp_elem;
	int		idx;

	size = mini_lstlen(env_lst);
	idx = 0;
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (0);
	env_arr[size] = 0;
	while (env_lst)
	{
		temp_elem = ft_strjoin(env_lst->key, "=");
		elem = ft_strjoin(temp_elem, env_lst->value);
		env_arr[idx] = elem;
		free(temp_elem);
		env_lst = env_lst->next;
		idx++;
	}
	return (env_arr);
}

int	init_env_lst(t_lst **env_lst, char *envp[])
{
	t_lst	*new;
	int		size;
	int		idx;

	idx = 0;
	while (envp[idx])
		idx++;
	size = idx;
	idx = 0;
	while (idx < size - 1)
	{
		new = split_key_value(envp[idx], idx);
		mini_lstaddback(env_lst, new);
		idx++;
	}
	return (0);
}
