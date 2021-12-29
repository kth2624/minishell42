#include "minishell.h"

int	mini_echo(char *argv[], int flag)
{
	int	idx;

	if (flag == 0)
	{
		idx = 1;
		while (argv[idx])
		{
			printf("%s", argv[idx]);
			if (argv[idx] != 0)
				printf(" ");
			idx++;
		}
		printf("\n");
	}
	else if (flag == 1)
	{
		idx = 2;
		if (!argv[idx])
		 	return (1);
		while (argv[idx + 1])
		{
			printf("%s ", argv[idx]);
			idx++;
		}
		printf("%s", argv[idx]);
	}
	return (0);
}
