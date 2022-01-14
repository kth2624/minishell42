
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

int	exec_func(char *path, t_cmd *cmd, t_lst **env_lst)
{
	char	**env_arr;
	int		fd_in;
	int		fd_out;

	if (!cmd)
		return (1);
	fd_in = 0;
	fd_out = 1;
	if (!cmd->argv || !path || !env_lst)
		return (1);
	check_redirection(cmd, &fd_in, &fd_out);
	if (exec_built_in_func(cmd->argv, env_lst) == 1)
	{
		env_arr = make_env_arr(*env_lst);
		exec_path(path, cmd->argv, env_arr, &fd_in, &fd_out);
		free_memory(env_arr);
	}
	if (fd_in != 0)
		dup2(0, fd_in);
	if (fd_out != 1)
		dup2(1, fd_out);
	free(path);
	return (0);
}

int	minishell(char *envp[])
{
	t_lst	*env_lst;
	char	*input;
	char	*path;
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
			input = ft_strdup("exit");
			printf("%s\n", input);
			free(input);
			mini_exit();
		}
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
