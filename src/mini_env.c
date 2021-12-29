#include "minishell.h"

int	mini_env(t_lst *env_lst)
{
	t_lst	*head;
	int		size;
	int		cnt;

	size = mini_lstlen(env_lst);
	cnt = 0;
	while (cnt < size)
	{
		head = env_lst;
		while (head)
		{
			if (head->idx == cnt)
			{
				printf("%s=%s\n", head->key, head->value);
				cnt++;
			}
			head = head->next;
		}
	}
	printf("_=usr/bin/env\n");
	return (0);
}
