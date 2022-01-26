#include "minishell.h"

static int	write_side_case_with_option(char *argv[], char **split_str)
{
	int		idx;
	int		len;

	idx = 2;
	if (ft_strcmp(argv[0], "echo") == 0 && ft_strcmp(argv[1], "-n") == 0)
		return (0);
	while (split_str[idx + 1])
	{
		len = ft_strlen(split_str[idx]);
		write(1, split_str[idx], len);
		if (split_str[idx] != 0)
			write(1, " ", 1);
		idx++;
	}
	len = ft_strlen(split_str[idx]);
	write(1, split_str[idx], len);
	return (1);
}

static int	write_side_case(char *argv[], char **split_str)
{
	int		idx;
	int		len;

	idx = 1;
	if (ft_strcmp(argv[0], "echo") == 0)
		return (0);
	while (split_str[idx])
	{
		len = ft_strlen(split_str[idx]);
		write(1, split_str[idx], len);
		if (split_str[idx] != 0)
			write(1, " ", 1);
		idx++;
	}
	printf("\n");
	return (1);
}

static void	write_without_option(char *argv[], char **split_str)
{
	int		idx;
	int		len;

	idx = 1;
	if (write_side_case(argv, split_str) != 0)
		return ;
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

static void	write_with_option(char *argv[], char **split_str)
{
	int	idx;
	int	len;

	idx = 2;
	if (write_side_case_with_option(argv, split_str) != 0)
		return ;
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
	char	**split_str;

	if (argv[1] == 0)
	{
		split_str = ft_split(argv[0], ' ');
		if (ft_strcmp(split_str[1], "-n") == 0)
			flag = 1;
	}
	if (flag == 0)
		write_without_option(argv, split_str);
	else if (flag == 1)
		write_with_option(argv, split_str);
	free_2dim_arr(split_str);
	return (0);
}
