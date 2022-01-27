#include "minishell.h"
#include <limits.h>

static long long	ft_atoll(char *str)
{
	unsigned long long	ret;
	long long			sign;

	ret = 0;
	sign = 1;
	while (*str && ((9 <= *str && *str <= 13) || *str == ' '))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && ('0' <= *str && *str <= '9'))
	{
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	if (ret >= LONG_MAX && sign == 1)
		return (LONG_MAX);
	if (ret >= ((unsigned long)LONG_MIN) && sign == -1)
		return (LONG_MIN);
	return (ret * sign);
}

static int	nan_error(long long arg_num, char *arg_str)
{
	if (arg_num == LONG_MAX)
	{
		if (ft_strcmp(arg_str, "9223372036854775807") != 0)
		{
			write(2, "bash: exit: ", 13);
			write(2, arg_str, ft_strlen(arg_str));
			write(2, ": numeric argument required\n", 29);
			return (255);
		}
	}
	else if (arg_num == LONG_MIN)
	{
		if (ft_strcmp(arg_str, "-9223372036854775808") != 0)
		{
			write(2, "bash: exit: ", 13);
			write(2, arg_str, ft_strlen(arg_str));
			write(2, ": numeric argument required\n", 29);
			return (255);
		}
	}
	return (arg_num);
}

static int	check_numeric_arg(int argc, char *argv[])
{
	int	argv_idx;
	int	str_idx;

	argv_idx = 1;
	while (argv_idx < argc)
	{
		str_idx = 0;
		while (argv[str_idx])
		{
			if (!ft_isdigit(argv[argv_idx][str_idx]))
			{
				write(2, "bash: exit: ", 13);
				write(2, argv[argv_idx], ft_strlen(argv[argv_idx]));
				write(2, ": numeric argument required\n", 29);
				return (255);
			}
			str_idx++;
		}
		argv_idx++;
	}
	return (-1);
}

static long long	check_error(int argc, char *argv[])
{
	long long	arg_num;

	arg_num = 0;
	if (argc < 2)
		return (arg_num);
	if (check_numeric_arg(argc, argv) > 0)
		return (255);
	arg_num = ft_atoll(argv[1]);
	arg_num = nan_error(arg_num, argv[1]);
	if (argc > 2)
	{
		write(2, "minishell42: exit: too many arguments\n", 39);
		return (-2);
	}
	return (arg_num);
}

int	mini_exit(char *argv[])
{
	int	argc;
	int	exit_arg;

	if (!argv)
		exit(g_status);
	argc = 0;
	while (argv[argc])
		argc++;
	exit_arg = check_error(argc, argv);
	if (exit_arg == -2)
	{
		g_status = 1;
		return (1);
	}
	exit_arg = (char)exit_arg;
	exit(exit_arg);
}
