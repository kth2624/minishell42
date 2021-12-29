#include "minishell.h"

int	cnt_quote_len(char *input, int *idx)
{
	int len;

	len = 0;
	(*idx)++;
	while (input[*idx] && input[*idx] != '\'')
		(*idx)++;
	len++;
	(*idx)++;
	return (len);
}

char *parse_case_quote(char *input, int *i)
{
	int len;
	char *temp;

	len = 0;
	(*i)++;
	while (input[*i + len] && input[*i + len] != '\'')
		len++;
	temp = ft_substr(input, *i, len);
	*i += len;
	return (temp);
}