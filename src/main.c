
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
	fd_in = 0;
	fd_out = 1;
	if (!cmd->argv || !env_lst)
		return (1);
	idx = 0;
	/*
	while (cmd)
	{
		cat < ls < ls < ls
		if (next_flag == PIPE)
			pid = fork();
		pipe(pid, ); >>> if (flag 확인 > pipe > fd)
		redirection(); if (redirection == )
		exec_func(); case 1: built_in, case 2: path;

		fork()
		exec_funfc()
	}*/
	// printf("next = %d\n",cmd->next_flag);
	while(cmd)
	{
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
		// check_redirection(cmd, &fd_in, &fd_out);
		if (cmd->next_flag )
			pid = fork();
		if(pid == 0)
		{
			if (fd_in != 0)
				dup2(fd_in, 0);
			if (fd_out != 1)
				dup2(fd_out, 1);
			if(cmd->pre_flag == PIPE)
				dup2(fd[idx-1][0], fd_in);
			if(cmd->next_flag == PIPE)
				dup2(fd[idx][1], fd_out);
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
			close(fd[idx-1][0]);
			close(fd[idx][1]);
			wait(&status);
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
		handle_signal();
		input = readline("minishell42 $ ");
		/*if (!input)
		{
			input = ft_strdup("exit");
			printf("%s\n", input);
			free(input);
			mini_exit();
		}*/
		if (ft_strcmp("", input) == 0)
		{
			free(input);
			continue ;
		}
		cmd = first_parsing(input, env_lst);
		printf("cmd-> %s\n",cmd->argv[0]);
		exec_func(cmd, &env_lst);
		add_history(input);
		free(input);
	}
	// if (fd_in != 0)
	// 	dup2(0, fd_in);
	// if (fd_out != 1)
	// 	dup2(1, fd_out);
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
