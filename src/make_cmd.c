#include "minishell.h"

t_cmd	*mini_cmdnew(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->argv = 0;
	cmd->fd_in = 0;
	cmd->pipe[0] = 0;
	cmd->pipe[1] = 1;
	cmd->fd_out = 1;
	cmd->is_pipe = 0;
	cmd->next = 0;
	return (cmd);
}

void	mini_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*head;

	if (!(*cmd))
	{
		*cmd = new;
		return ;
	}
	head = *cmd;
	while (head->next)
		head = head->next;
	head->next = new;
	return ;
}

static int	cnt_pipe(t_token *tokens)
{
	t_token	*token;
	int		cnt;

	token = tokens;
	cnt = 0;
	while (token)
	{
		if (token->type == PIPE)
			cnt++;
		token = token->next;
	}
	return (cnt);
}

t_cmd	*set_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*token;
	int		len;
	t_cmd	*new;

	token = tokens;
	len = cnt_pipe(tokens) + 1;
	cmd = 0;
	while (len--)
	{
		if (!cmd)
			cmd = mini_cmdnew();
		else
		{
			new = mini_cmdnew();
			mini_cmdadd_back(&cmd, new);
		}
	}
	return (cmd);
}

t_cmd	*make_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*token;
	t_cmd	*head;

	cmd = set_cmd(tokens);
	token = tokens;
	head = cmd;
	while (token)
	{
		head->argv = make_argv(token);
		check_redirection(token, &head->fd_in, &head->fd_out);
		pipe(head->pipe);
		while (token && token->type != PIPE)
			token = token->next;
		if (token)
		{
			token = token->next;
			head->is_pipe = 1;
		}
		if (token && head)
			head = head->next;
	}
	return (cmd);
}
