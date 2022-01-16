#include "minishell.h"

static void	write_without_option(char *argv[])
{
	int	idx;
	int	len;

	idx = 1;
	while (argv[idx])
	{
		len = ft_strlen(argv[idx]);
		write(1, argv[idx], len);
		if (argv[idx] != 0)
			write(1, " ", 1);
		idx++;
	}
	printf("\n");
}

static void	write_with_option(char *argv[])
{
	int	idx;
	int	len;

	idx = 2;
	while (argv[idx + 1])
	{
		len = ft_strlen(argv[idx]);
		write(1, argv[idx], len);
		if (argv[idx] != 0)
			write(1, " ", 1);
		idx++;
	}
	len = ft_strlen(argv[idx]);
	write(1, argv[idx], len);
}

int	mini_echo(char *argv[], int flag)
{
	if (flag == 0)
		write_without_option(argv);
	else if (flag == 1)
		write_with_option(argv);
	return (0);
}
