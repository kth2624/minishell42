#include "minishell.h"

int	exec_func(t_cmd *cmd, t_lst **env_lst)
{
	char	**env_arr;
	pid_t	pid;
	int		status;
	char	*path;
	char	**path_arr;
	t_cmd	*prev;
	int idx = 0;
	if (!cmd)
		return (1);
	if (!cmd->argv || !env_lst)
		return (1);
	//print_cmd(cmd);
	prev = 0;
	while(cmd)
	{
		path_arr = path_parsing(cmd->argv[0], *env_lst);
		pid = fork();
		if(pid == 0)
		{
			//	   fd[0][0]. [1]	fd[1][0] .[1]
			// echo hi | cat < a > b | ls
			// echo 프로세스의 입력 : 표준 입력
			//				출력 : fd[0][1]
			// cat 프로세스의 입력  : fd[0][0] 이 아니라 a의 fd
			//			   출력  : fd[1][1] 이 아니라 b이 fd
			// ls 프로세스의 입력   : fd[1][0]
			//			  출력   : 표준 출력

			if (cmd->fd_in!= 0) {
				dup2(cmd->fd_in, 0);
				fprintf(stderr, "%s : fd_in = %d\n", cmd->argv[0], cmd->fd_in);
			}
			else if (prev && prev->is_pipe == 1) {
				dup2(prev->pipe[0], 0);
				fprintf(stderr, "%s : pre_flag = %d\n", cmd->argv[0], idx-1);
			}
			if (cmd->fd_out != 1) {
				dup2(cmd->fd_out, 1);
				fprintf(stderr, "%s : fd_out = %d\n", cmd->argv[0], cmd->fd_out);
			}
			else if(cmd->is_pipe == 1) {
				dup2(cmd->pipe[1], 1);
				fprintf(stderr, "%s : next_flag = %d\n", cmd->argv[0], idx);
			}
			if (exec_built_in_func(cmd->argv, env_lst) == 1)
			{
				path = path_is_valid(cmd->argv[0], path_arr);
				env_arr = make_env_arr(*env_lst);
				exec_path(path, cmd->argv, env_arr);
			}
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (prev)
				close(prev->pipe[0]);
			close(cmd->pipe[1]);
		}
		else if (pid < 0)
			printf("%s\n", strerror(errno));
		prev = cmd;
		idx++;
		free_2dim_arr(path_arr);
		cmd = cmd->next;
	}
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
		handle_signal();
		input = readline("minishell42 $ ");

		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		cmd = first_parsing(input, env_lst);
		exec_func(cmd, &env_lst);
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