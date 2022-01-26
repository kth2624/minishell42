#include "minishell.h"

static int	print_err(char *path)
{
	printf("minishell42: %s: command not found\n", path);
	return (127);
}

void	set_g_status(void)
{
	if (g_status == 2)
		g_status = 130;
	else if (g_status == 3)
		g_status = 131;
	else
		g_status = WEXITSTATUS(g_status);
}

void	exec_path(t_cmd *cmd, t_cmd *prev, char **env_arr, char **path_arr)
{
	int		pid;
	char	*path;

	path = path_is_valid(cmd->argv[0], path_arr);
	pid = fork();
	if (pid > 0)
	{
		handle_signal_child();
		waitpid(pid, &g_status, 0);
		set_g_status();
		if (prev)
			close(prev->pipe[0]);
		close(cmd->pipe[1]);
		handle_signal();
	}
	else if (pid == 0)
	{
		set_redirect_and_pipe(cmd, prev);
		if (execve(path, cmd->argv, env_arr) == -1)
			exit(print_err(path));
	}
	else
		printf("%s\n", strerror(errno));
}
