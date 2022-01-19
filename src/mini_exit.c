#include "minishell.h"

int mini_exit(char *argv[])
{
    int argc;
    int exit_num;

    if (!argv)
        return (1);
    argc = 0;
    while (argv[argc])
        argc++;
    if (argc > 2)
        write(2, "minishell42: exit: too many arguments\n", 39);
    if (argc < 2)
        exit(0);
    exit_num = ft_atoi(argv[1]);
    exit_num = (char)exit_num;
    exit(exit_num);
}