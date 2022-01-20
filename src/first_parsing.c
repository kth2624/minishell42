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

void	change_env(t_list **tokens, t_lst *env_lst)
{
	t_list	*token;
	int		idx;
	char	*content;
	char	*env_str;

	token = *tokens;
	while (token)
	{
		idx = 0;
		while (content[idx])
		{
			if (content[idx] == '$')
			{
				content = ft_strdup(token->content);
				content[idx] = '\0';
				env_str = parse_case_doller(token->content, &idx, env_lst);
				content = mini_strjoin(content, env_str);
				free(token->content);
				token->content = content;
			}
			idx++;
		}
		token = token->next;
	}
	return ;
}

int	cut_case_spc(char *input, int *idx, t_list **tokens)
{
	int		len;
	char	*content;
	t_list	*token;

	len = 0;
	if (input[*idx + len] == '|' && len == 0)
	{
		content = ft_strdup("|");
		token = ft_lstnew(content);
		ft_lstadd_back(tokens, token);
		len++;
	}
	else if (input[*idx + len] == '<' && len == 0)
	{
		while (input[*idx + len] == '<')
			len++;
		content = ft_substr(input, *idx, len);
		token = ft_lstnew(content);
		ft_lstadd_back(tokens, token);
	}
	else if (input[*idx + len] == '>' && len == 0)
	{
		while (input[*idx + len] == '>')
			len++;
		content = ft_substr(input, *idx, len);
		token = ft_lstnew(content);
		ft_lstadd_back(tokens, token);
	}
	return (len);
}

void	cut_case_pipe(char *input, int *idx, t_list **tokens)
{
	int		len;
	char	*content;
	t_list	*token;

	len = 0;
	while (input[*idx + len] != '|' && input[*idx + len] != '>' && input[*idx + len] != '<' && input[*idx + len])
		len++;
	if ((input[*idx + len] == '|' || input[*idx + len] == '>' || input[*idx + len] == '<') && len == 0)
		len += cut_case_spc(input, idx, tokens);
	else
	{
		content = ft_substr(input, *idx, len);
		token = ft_lstnew(content);
		ft_lstadd_back(tokens, token);
	}
	*idx += len;
}

t_list	*fill_token(char *input, t_list **tokens)
{
	int		idx;

	idx = 0;
	while (input[idx])
	{
		cut_case_pipe(input, &idx, tokens);
	}
}

t_cmd	*first_parsing(char *input, t_lst *env_lst)
{
	t_list	*tokens;
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
	fill_token(input, &tokens);
	change_env(&tokens, env_lst);
	cmd = make_cmd(tokens, env_lst);
	free_token(tokens);
	return (cmd);
}
