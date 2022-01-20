#include "minishell.h"

int	unset_func(t_lst **env_lst, char *key)
{
	t_lst	*curr;
	t_lst	*next;

	curr = *env_lst;
	next = curr->next;
	if (ft_strcmp(curr->key, key) == 0)
	{
		*env_lst = next;
		free(curr);
		return (0);
	}
	while (curr->next)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			next = curr->next->next;
			free(curr->next);
			curr->next = 0;
			curr->next = next;
			return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int	mini_unset(t_lst **env_lst, char *argv[])
{
	int	idx;
	int	ret;

	idx = 0;
	while (argv[idx])
	{
		ret = unset_func(env_lst, argv[idx]);
		idx++;
	}
	return (ret);
}
