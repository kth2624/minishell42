#include "minishell.h"

t_list	*make_token(char *input, int len, int *idx)
{
	t_list	*token;
	char	*content;

	if (input[*idx + len] == '|' && len == 0)
	{
		len++;
		content = ft_substr(input, *idx, len);
		token = ft_lstnew(content);
	}
	else if (input[*idx + len] == '>' && len == 0)
	{
		while (input[*idx + len] == '>')
			len++;
		content = ft_substr(input, *idx, len);
		token = ft_lstnew(content);
	}
	else if (input[*idx + len] == '<' && len == 0)
	{
		while (input[*idx + len] == '<')
			len++;
		content = ft_substr(input, *idx, len);
		token = ft_lstnew(content);
	}
	else
	{
		content = ft_substr(input, *idx, len);
		token = ft_lstnew(content);
	}
	(*idx) += len;
	return (token);
}

t_list	*read_input(char *input)
{
	static int	idx;
	int			len;
	t_list		*token;

	if (!input[idx])
	{
		idx = 0;
		return (0);
	}
	while (input[idx] == ' ')
		idx++;
	len = 0;
	while (input[idx + len] != '|' && \
	input[idx + len] != '<' && input[idx + len] != '>' && input[idx + len] != 0)
		len++;
	token = make_token(input, len, &idx);
	return (token);
}

void	fill_tokens(t_list **tokens, char *input)
{
	t_list	*token;
	t_list	*tmp;

	token = read_input(input);
	while (token)
	{
		ft_lstadd_back(tokens, token);
		token = read_input(input);
	}
	tmp = *tokens;
	while (tmp)
	{
		printf("tokens->content : %s\n", tmp->content);
		tmp = tmp->next;
	}
}

t_list	*first_parsing(char *input)
{
	t_list	*tokens;

	if (!input[0])
		return (0);
	if (!is_valid_quote(input))
	{
		printf("quote error\n");
		return (0);
	}
	tokens = 0;
	fill_tokens(&tokens, input);
	return (tokens);
}
