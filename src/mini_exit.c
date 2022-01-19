#include "minishell.h"
#include <limits.h>

static long long    ft_atoll(char *str)
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
	return (ret * sign);
}

static void nan_error(long long arg_num, char *arg_str)
{
    if (arg_num == LONG_MAX)
    {
        if (ft_strcmp(arg_str, "9223372036854775807") != 0)
        {
            write(2, "bash: exit: ", 13);
            write(2, arg_str, ft_strlen(arg_str));
            write(2, ": numeric argument required\n", 29);
        }
    }
    else if (arg_num == LONG_MIN)
    {
        if (ft_strcmp(arg_str, "-9223372036854775808") != 0)
        {
            write(2, "bash: exit: ", 13);
            write(2, arg_str, ft_strlen(arg_str));
            write(2, ": numeric argument required\n", 29);
        }
    }
}

static int  check_error(int argc, char *argv[])
{
    long long   arg_num;

    arg_num = 0;
    if (argc > 2)
        write(2, "minishell42: exit: too many arguments\n", 39);
    if (argc < 2)
        return (arg_num);
    arg_num = ft_atoll(argv[1]);
    nan_error(arg_num, argv[1]);
    return (arg_num);
}

int mini_exit(char *argv[])
{
    int argc;
    int exit_arg;

    if (!argv)
        exit(0);
    argc = 0;
    while (argv[argc])
        argc++;
    exit_arg = check_error(argc, argv);
    exit_arg = (char)exit_arg;
    exit(exit_arg);
}