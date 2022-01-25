#include "minishell.h"

extern int	g_status;

int	exec_path(t_cmd *cmd, t_lst *env_lst, t_cmd *prev)
{
	int		ret;
	int		pid;
	char	**env_arr;
	char	**path_arr;
	char	*path;

	env_arr = make_env_arr(env_lst);
	path_arr = path_parsing(cmd->argv[0], env_lst);
	path = path_is_valid(cmd->argv[0], path_arr);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &g_status, 0);
		if (prev)
			close(prev->pipe[0]);
		close(cmd->pipe[1]);
		free_2dim_arr(path_arr);
		free_2dim_arr(env_arr);
	}
	else if (pid == 0)
	{
		//set_redirection(cmd, prev);
		if (cmd->fd_in != 0)
			dup2(cmd->fd_in, 0);
		if (prev && prev->is_pipe == 1)
			dup2(prev->pipe[0], 0);
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, 1);
		if (cmd->is_pipe == 1)
			dup2(cmd->pipe[1], 1);
		ret = execve(path, cmd->argv, env_arr);
		if (ret == -1)
		{
			printf("minishell42: %s: command not found\n", path);
			exit(1);
		}
	}
	else
		printf("%s\n", strerror(errno));
}