#include "minishell.h"

void    print_token(t_token *tokens)
{
    t_token	*temp;

    temp = tokens;
    while (temp)
    {
        printf("token->content : %s\n", temp->content);
		printf("token->type : %d\n", temp->type);
        temp = temp->next;
    }
}

void	print_2dim_arr(char **arr)
{
	int	idx;

	idx = 0;
	while (arr[idx])
	{
		printf("arr[%d] : %s\n", idx, arr[idx]);
		idx++;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*temp;
	int		idx;

	temp = cmd;
	while (temp)
	{
		idx = 0;
		print_2dim_arr(temp->argv);
		printf("fd_in : %d fd_out : %d\n", temp->fd_in, temp->fd_out);
		printf("pipe[0] : %d pipe[1] : %d\n", temp->pipe[0], temp->pipe[1]);
		printf("is_pipe : %d\n", temp->is_pipe);
		printf("-----------------------------------\n");
		temp = temp->next;
	}
}