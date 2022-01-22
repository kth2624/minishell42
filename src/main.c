#include "minishell.h"

int		is_redirection(int flag)
{
	if(flag == REDIRECT1 || flag == REDIRECT2 ||flag == REDIRECT3 ||flag == REDIRECT4)
		return (1);
	return (0);
}

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

int	exec_func(t_cmd *cmd, t_lst **env_lst)
{
	char	**env_arr;
	int		fd_in;
	int		fd_out;
	int fd[cmd->size][2];
	int idx;
	pid_t pid;
	int status;
	char	*path;
	char	**path_arr;
	t_cmd *curr;

	if (!cmd)
		return (1);
	if (!cmd->argv || !env_lst)
		return (1);
	idx = 0;
	while(cmd)
	{
		fd_in = 0;
		fd_out = 1;
		path_arr = path_parsing(cmd->argv[0], *env_lst);
		pipe(fd[idx]);
		curr = cmd;
		if(is_redirection(cmd->next_flag))
		{
			while(is_redirection(cmd->next_flag))
			{
				check_redirection(cmd, &fd_in, &fd_out);
				cmd = cmd->next;
			}
		}

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

			if (fd_in != 0) {
				dup2(fd_in, 0);
				// fprintf(stderr, "%s : fd_in = %d\n", curr->argv[0], fd_in);
			}
			else if (curr->pre_flag == PIPE) {
				dup2(fd[idx-1][0], 0);
				// fprintf(stderr, "%s : pre_flag = %d\n", curr->argv[0], idx-1);
			}
			if (fd_out != 1) {
				dup2(fd_out, 1);
				// fprintf(stderr, "%s : fd_out = %d\n", curr->argv[0], fd_out);
			}
			else if(cmd->next_flag == PIPE) {
				dup2(fd[idx][1], 1);
				// fprintf(stderr, "%s : next_flag = %d\n", curr->argv[0], idx);
			}
			if (exec_built_in_func(curr->argv, env_lst) == 1)
			{
				path = path_is_valid(curr->argv[0], path_arr);
				env_arr = make_env_arr(*env_lst);
				exec_path(path, curr->argv, env_arr, &fd_in, &fd_out);
				free_memory(env_arr);
			}
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (idx > 1)
				close(fd[idx-1][0]);
			close(fd[idx][1]);
		}
		else if (pid < 0)
			printf("%s\n", strerror(errno));
		idx++;
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
	//	handle_signal();
		input = readline("minishell42 $ ");

		if (!input)
		{
			printf("exit\n");
			exit(0);
		}
		if(ft_strlen(input) == 0)
			continue ;
		cmd = first_parsing(input, env_lst);
		// printf("cmd-> %s\n",cmd->argv[0]);
		exec_func(cmd, &env_lst);
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