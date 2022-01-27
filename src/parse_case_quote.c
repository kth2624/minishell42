#include "minishell.h"

char	*parse_case_quote(char *input, int *i)
{
	int		len;
	char	*temp;

	len = 0;
	(*i)++;
	while (input[*i + len] && input[*i + len] != '\'')
		len++;
	temp = ft_substr(input, *i, len);
	*i += len;
	return (temp);
}
