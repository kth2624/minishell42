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
			handle_redirection4(curr, fd_in, fd_out);
		curr = curr->next;
	}
}

void	set_redirection(t_cmd *cmd, t_cmd *prev)
{
	//if (cmd->fd_in != 0)
	//	dup2(cmd->fd_in, 0);
	//if (prev && prev->is_pipe == 1)
	//	dup2(prev->pipe[0], 0);
	//if (cmd->fd_out != 1)
	//	dup2(cmd->fd_out, 1);
	//if (cmd->is_pipe == 1)
	//	dup2(cmd->pipe[1], 1);
}