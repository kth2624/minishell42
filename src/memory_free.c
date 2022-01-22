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

void    free_token(t_token *tokens)
{
    t_token  *token;

    token = tokens;
	while (token)
	{
		free(token->content);
		free(token);
		token = token->next;
	}
}

void    free_cmd(t_cmd *cmd)
{
    t_cmd   *tmp;

    tmp = cmd;
	while (tmp)
	{
		free_2dim_arr(tmp->argv);
		free(tmp);
		tmp = tmp->next;
	}
}