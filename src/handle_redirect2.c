#include "minishell.h"

void	set_redirect_and_pipe(t_cmd *cmd, t_cmd *prev)
{
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	else if (prev && prev->is_pipe == 1)
		dup2(prev->pipe[0], 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
	else if (cmd->is_pipe == 1)
		dup2(cmd->pipe[1], 1);
}
