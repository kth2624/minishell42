#include "minishell.h"

void	free_2dim_arr(char **str)
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

void    free_token(t_list *tokens)
{
    t_list  *token;

    token = tokens;
	while (token)
	{
		free(token->content);
		token = token->next;
	}
	free(tokens);
}

void    free_cmd(t_cmd *cmd)
{
    t_cmd   *tmp;
    int     idx;

    tmp = cmd;
	free_2dim_arr(cmd->argv);
	free(tmp);
}