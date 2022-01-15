
#include "minishell.h"

void	free_memory(char **str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		free(str[idx]);
		idx++;
	}
	free(str);
}

int	exec_func(char **path, t_cmd *cmd, t_lst **env_lst)
{
	char	**env_arr;
	int		fd_in;
	int		fd_out;
	int fd[cmd->size][2];
	int idx;
	pid_t pid;
	int status;

	if (!cmd)
		return (1);
	fd_in = 0;
	fd_out = 1;
	if (!cmd->argv || !path || !env_lst)
		return (1);
	idx = 0;
	// printf("cmd size = %d\n",)
	while(cmd)
	{
		pipe(fd[idx]);
		// printf("cmd idx %d\n",idx);
		// printf("cmd pre %d next %d\n",cmd->pre_flag,cmd->next_flag);
		pid = fork();
		if(pid == 0)
		{
			if(cmd->pre_flag == PIPE)
			{
				dup2(fd[idx-1][0], 0);
			}
			if(cmd->next_flag == PIPE)
			{
				dup2(fd[idx][1], 1);
			}

			if (exec_built_in_func(cmd->argv, env_lst) == 1)
			{
				write(2, "hi\n\n", 4);
				env_arr = make_env_arr(*env_lst);
				exec_path(path, cmd->argv, env_arr, &fd_in, &fd_out);
				write(2, "bye\n\n", 5);
				free_memory(env_arr);
			}
		}
		else if (pid > 0)
		{
			close(fd[idx-1][0]);
			close(fd[idx][1]);
			wait(&status);
		}
		idx++;
		cmd = cmd->next;

	}
	free_memory(path);
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
		input = readline("minishell42 $ ");
		if (!input)
			return (0);
		cmd = first_parsing(input, env_lst);
		if (cmd)
			path = path_parsing(cmd->argv[0], env_lst);
		exec_func(path, cmd, &env_lst);
		add_history(input);
		free(input);
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
