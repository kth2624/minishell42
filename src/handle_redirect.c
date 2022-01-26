#include "minishell.h"

static void	handle_heredoc(t_token *curr, int *fd_in, int *fd_out)
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

static int	redirect_syntax_error(t_token *curr, int *fd_in)
{
	t_token	*head;

	head = curr;
	while (head)
	{
		if (head->type == REDIRECT1 || head->type == REDIRECT2 || \
		head->type == REDIRECT3 || head->type == REDIRECT4)
		{
			if (!head->next)
			{
				*fd_in = -1;
				write(2, "minishell42: syntax error near\
 unexpected token `newline'\n", 59);
				return (1);
			}
		}
		head = head->next;
	}
	return (0);
}

static int	redirect_file_error(t_token *curr, int fd_in)
{
	if (fd_in < 0)
	{
		write(2, "minishell42: ", 14);
		write(2, curr->next->content, ft_strlen(curr->next->content));
		write(2, ": No such file or directory\n", 29);
		return (1);
	}
	return (0);
}

static void	check_type_and_open_file(t_token *curr, int *fd_in, int *fd_out)
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
		redirect_file_error(curr, *fd_in);
	}
	else if (curr->type == REDIRECT3)
	{
		if (*fd_out != 1)
			close(*fd_out);
		*fd_out = \
		open(curr->next->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (curr->type == REDIRECT4)
		handle_heredoc(curr, fd_in, fd_out);
}

void	check_redirection(t_token *tokens, int *fd_in, int *fd_out)
{
	t_token	*curr;

	curr = tokens;
	if (redirect_syntax_error(curr, fd_in) == 1)
		return ;
	while (curr && curr->type != PIPE)
	{
		check_type_and_open_file(curr, fd_in, fd_out);
		curr = curr->next;
	}
}
