
#include "minishell.h"

int	exec_func(t_cmd *cmd, t_lst **env_lst)
{
	char	**env_arr;
	pid_t	pid;
	int		status;
	char	*path;
	char	**path_arr;

	if (!cmd)
		return (1);
	if (!cmd->argv || !env_lst)
		return (1);
	env_arr = make_env_arr(*env_lst);
	while (cmd)
	{
		if (cmd->fd_in != 0)
			dup2(0, cmd->fd_in);
		if (cmd->fd_out != 1)
			dup2(1, cmd->fd_out);
		if (exec_built_in_func(cmd->argv, env_lst) == 1)
		{
			path = path_parsing(cmd->argv[0], *env_lst);
			exec_path(path, cmd->argv, env_arr, &cmd->fd_in, &cmd->fd_out);
		}
	}
/*	while(cmd)
	{
		path_arr = path_parsing(cmd->argv[0], *env_lst);
		pipe(fd[idx]);
		pid = fork();
		if(pid == 0)
		{
			if(cmd->pre_flag == PIPE)
				dup2(fd[idx-1][0], 0);
			if(cmd->next_flag == PIPE)
				dup2(fd[idx][1], 1);
			if (fd_in != 0)
				dup2(0, fd_in);
			if (fd_out != 1)
				dup2(1, fd_out);
			if (exec_built_in_func(cmd->argv, env_lst) == 1)
			{
				path = path_is_valid(cmd->argv[0], path_arr);
				env_arr = make_env_arr(*env_lst);
				exec_path(path, cmd->argv, env_arr, &fd_in, &fd_out);
				free_memory(env_arr);
			}
		}
		else if (pid > 0)
		{
			close(fd[idx-1][0]);
			close(fd[idx][1]);
			wait(&status);
		}
		else if (pid < 0)
			printf("%s\n", strerror(errno));
		idx++;
		cmd = cmd->next;
	}*/
	return (0);
}

int	minishell(char *envp[])
{
	t_lst	*env_lst;
	char	*input;
	char	**path;
	t_cmd	*cmd;

	env_lst = 0;
	if (!env_lst)
		init_env_lst(&env_lst, envp);
	while (1)
	{
	//	handle_signal();
		input = readline("minishell42 $ ");
		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		cmd = first_parsing(input, env_lst);
		print_cmd(cmd);
		//exec_func(cmd, &env_lst);
		add_history(input);
		free(input);
		free_cmd(cmd);
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	printf("Hello minishell!\n");
	minishell(envp);

	return (0);
}
