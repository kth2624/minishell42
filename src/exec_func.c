#include "minishell.h"

static void	handle_redirection4(t_token *curr, int *fd_in, int *fd_out)
{
	int		temp[2];
	char	*input;

	if (*fd_in != 0)
		close(*fd_in);
	pipe(temp);
	input = readline("> ");
	while (input && ft_strcmp(input, curr->next->content) != 0)
	{
		write(temp[1], input, ft_strlen(input));
		write(temp[1], "\n", 1);
		input = readline("> ");
	}
	close(temp[1]);
	*fd_in = temp[0];
}

void	check_redirection(t_token *tokens, int *fd_in, int *fd_out)
{
	t_token	*curr;

	curr = tokens;
	while (curr && curr->type != PIPE)
	{
		if (curr->type == REDIRECT1)
		{
			if (*fd_out != 1)
				close(*fd_out);
			*fd_out = \
			open(curr->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (curr->type == REDIRECT2)
		{
			if (*fd_in != 0)
				close(*fd_in);
			*fd_in = open(curr->next->content, O_RDONLY);
		}
		else if (curr->type == REDIRECT3)
		{
			if (*fd_out != 1)
				close(*fd_out);
			*fd_out = \
			open(curr->next->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		else if (curr->type == REDIRECT4)
			handle_redirection4(curr, *fd_in, *fd_out);
		curr = curr->next;
	}
}

int	exec_path(char *path, char *argv[], char *env_arr[])
{
	int		ret;

	ret = execve(path, argv, env_arr);
	if (ret == -1)
	{
		printf("minishell42: %s: command not found\n", path);
		exit(1);
	}
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
		mini_cd(argv, *env_lst);
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
	exit(0);
}
