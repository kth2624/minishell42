#include "minishell.h"

int	get_cmd_size(t_cmd *cmd)
{
	int i;

	i = 0;
	while(cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

t_cmd	*first_parsing(char *input, t_lst *env_lst)
{
	t_token	*tokens;
	t_cmd	*cmd;
	int size;

	if (!input[0] || !ft_isprint(input[0]))
		return (0);
	if (!is_valid_quote(input))
	{
		printf("quote error\n");
		return (0);
	}
	tokens = 0;
	tokens = tokenize(input);
	fill_token_type(tokens);
	convert_content(&tokens, env_lst);
	cmd = make_cmd(tokens, env_lst);
	free_token(tokens);
	return (cmd);
}
