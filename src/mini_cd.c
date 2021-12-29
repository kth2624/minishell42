
#include "minishell.h"

int	mini_cd(char *argv[])
{
	char	*err_msg;
	char	*path;

	path = argv[1];
	if (chdir(path) == -1)
	{
		printf("minishell42: cd: ");
		err_msg = strerror(errno);
		printf("%s: ", path);
		printf("%s\n", err_msg);
		return (1);
	}
	return (0);
}
