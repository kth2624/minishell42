#include "minishell.h"

extern int	g_status;

int	is_built_in(char *argv[])
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (1);
	else
		return (0);
}

int	exec_built_in_func(char *argv[], t_lst **env_lst)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			ret = mini_echo(argv, 1);
		else
			ret = mini_echo(argv, 0);
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
		ret = mini_cd(argv, *env_lst);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ret = mini_pwd();
	else if (ft_strcmp(argv[0], "unset") == 0)
		ret = mini_unset(env_lst, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		ret = mini_export(env_lst, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		ret = mini_env(*env_lst);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ret = mini_exit(argv);
	return (ret);
}

static void	exec_fork_case(t_cmd *cmd, t_lst **env_lst, t_cmd *prev)
{
	int	pid;
	
	pid = fork();
	//set_redirection(cmd);
	if (pid == 0)
	{
		set_redirection(cmd, prev);
		if (cmd->fd_in != 0)
			dup2(cmd->fd_in, 0);
		if (prev && prev->is_pipe == 1)
			dup2(prev->pipe[0], 0);
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, 1);
		if (cmd->is_pipe == 1)
			dup2(cmd->pipe[1], 1);
		g_status = exec_built_in_func(cmd->argv, env_lst);
		exit(g_status);
	}
	else if (pid > 0)
	{
		waitpid(pid, &g_status, 0);
		if (prev)
			close(prev->pipe[0]);
		close(cmd->pipe[1]);
	}
	else if (pid < 0)
		printf("%s\n", strerror(errno));
}

void exec_built_in(t_cmd *cmd, t_lst **env_lst, t_cmd *prev)
{
	//set_redirection(cmd, prev);
	if (cmd->is_pipe != 0)
	{
		exec_fork_case(cmd, env_lst, prev);
	}
	else
	{
		if (cmd->fd_in != 0)
			dup2(cmd->fd_in, 0);
		if (prev && prev->is_pipe == 1)
			dup2(prev->pipe[0], 0);
		if (cmd->fd_out != 1)
			dup2(cmd->fd_out, 1);
		if (cmd->is_pipe == 1)
			dup2(cmd->pipe[1], 1);
		exec_built_in_func(cmd->argv, env_lst);	
	}
}