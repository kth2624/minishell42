#include "minishell.h"

static void	split_token(t_token **tokens, t_token *curr, t_token *prev)
{
	char	**split_str;
	t_token	*new;
	t_token	*next_token;
	int		idx;

	split_str = ft_split(curr->content, ' ');
	if (!prev)
	{
		free(curr->content);
		curr->content = ft_strdup(split_str[0]);
		new = mini_tokennew(ft_strdup(split_str[1]));
		mini_tokenadd_back(tokens, new);
	}
	else
	{
		next_token = curr->next;
		free(curr->content);
		curr->content = ft_strdup(split_str[0]);
		new = mini_tokennew(ft_strdup(split_str[1]));
		while (curr->next != next_token)
			curr = curr->next;
		curr->next = new;
		new->next = next_token;
	}
	free(curr->content);
	free_2dim_arr(split_str);
}

static void	recheck_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;
	int		idx;

	curr = *tokens;
	prev = 0;
	while (curr)
	{
		idx = 0;
		while (curr->content[idx])
		{
			if (curr->content[idx] == ' ')
				split_token(tokens, curr, prev);
			idx++;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_cmd	*first_parsing(char *input, t_lst *env_lst)
{
	t_token	*tokens;
	t_cmd	*cmd;
	int		size;

	if (!input[0] || !ft_isprint(input[0]))
		return (0);
	if (!is_valid_quote(input))
	{
		printf("quote error\n");
		return (0);
	}
	tokens = 0;
	tokens = tokenize(input);
	// print_token(tokens);
	convert_content(&tokens, env_lst);
//	recheck_tokens(tokens);
//	print_token(tokens);
	fill_token_type(tokens);
	// print_token(tokens);
	cmd = make_cmd(tokens, env_lst);
	free_token(tokens);
	return (cmd);
}
