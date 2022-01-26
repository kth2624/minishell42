#include "minishell.h"

void	change_env_and_quote(t_token *token, t_lst *env_lst)
{
	char	*content;
	int		idx;
	char	*temp;

	content = token->content;
	idx = 0;
	temp = 0;
	while (content[idx])
	{
		if (content[idx] != '\'' && content[idx] != '"')
			temp = mini_strjoin(temp, \
			parse_case_none(content, &idx, env_lst), 0, 0);
		else if (content[idx] == '\'')
			temp = mini_strjoin(temp, parse_case_quote(content, &idx), 0, 0);
		else if (content[idx] == '"')
			temp = mini_strjoin(temp, \
			parse_case_dquote(content, &idx, env_lst), 0, 0);
		idx++;
	}
	free(token->content);
	token->content = temp;
}

void	convert_content(t_token **tokens, t_lst *env_lst)
{
	t_token	*token;

	token = *tokens;
	while (token)
	{
		change_env_and_quote(token, env_lst);
		token = token->next;
	}
}
