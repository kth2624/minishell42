
#include "minishell.h"

static int	get_str_arr_len(char *str[])
{
	int	idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

int	check_redirection(t_cmd *cmd, int *fd_in, int *fd_out)
{
	t_cmd	*curr;
	char	*file_name;

	curr = cmd;
	if (curr->next_flag != REDIRECT1 && curr->next_flag != REDIRECT2 && curr->next_flag != REDIRECT3 && curr->next_flag != REDIRECT4)
		return (0);
	file_name = cmd->next->argv[0];
	if (curr->next_flag == REDIRECT1)
		*fd_out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (curr->next_flag == REDIRECT2 || curr->next_flag == REDIRECT4)
		*fd_in = open(file_name, O_RDONLY);
	else if (curr->next_flag == REDIRECT3)
		*fd_out = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (*fd_in < 0 || *fd_out < 0)
		return (0);
	return (1);
}

int	exec_path(char *path, char *argv[], char *env_arr[], int *fd_in, int *fd_out)
{
	int			idx;
	int			pid;
	int			state;
	int			path_arr_len;
	int n;
	int			ret;

	idx = 0;
	// pid = fork();
	//if (pid > 0)
	//	waitpid(pid, &state, 0);
	//else if (pid == 0)
	//{
		// if (*fd_in != 0)
		// 	dup2(*fd_in, 0);
		// if (*fd_out != 1)
		// 	dup2(*fd_out, 1);

		ret = execve(path, argv, env_arr);
		if (ret == -1)
		{
			printf("minishell42: %s: command not found\n", path);
			//exit(1);
		}
	//}
	//else if (pid < 0)
	//exit(0);
	// return (0);
}

int	exec_built_in_func(char *argv[], t_lst **env_lst)
{
	if (ft_strcmp(argv[0], "echo") == 0)
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			mini_echo(argv, 1);
		else
			mini_echo(argv, 0);
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
		mini_cd(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(argv[0], "unset") == 0)
		mini_unset(env_lst, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		mini_export(env_lst, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		mini_env(*env_lst);
	else if (ft_strcmp(argv[0], "exit") == 0)
		mini_exit(argv);
	else
		return (1);
	//return (0);
	exit(0);
}
