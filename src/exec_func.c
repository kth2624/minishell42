#include "minishell.h"

int	exec_path(t_cmd *cmd, t_cmd *prev, char **env_arr, char **path_arr)
{
	int		pid;
	char	*path;

	path = path_is_valid(cmd->argv[0], path_arr);
	pid = fork();
	if (pid > 0)
	{
		handle_signal_child();
		waitpid(pid, &g_status, 0);
		if (prev)
			close(prev->pipe[0]);
		close(cmd->pipe[1]);
		handle_signal();
	}
	else if (pid == 0)
	{
		set_redirect_and_pipe(cmd, prev);
		if (execve(path, cmd->argv, env_arr) == -1)
		{
			printf("minishell42: %s: command not found\n", path);
			exit(1);
		}
	}
	else
		printf("%s\n", strerror(errno));
}
