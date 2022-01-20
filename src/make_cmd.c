#include "minishell.h"

int	get_spc(t_list *spc)
{
	char	*str;

	if (!spc)
		return (-1);
	str = spc->content;
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIRECT1);
	else if (ft_strcmp(str, "<") == 0)
		return (REDIRECT2);
	else if (ft_strcmp(str, ">>") == 0)
		return (REDIRECT3);
	else if (ft_strcmp(str, "<<") == 0)
		return (REDIRECT4);
	return (-1);
}

t_cmd	*mini_cmdnew(t_list *tokens, t_lst *env_lst, t_list *pre_token)
{
	t_cmd	*cmd;
	t_list	*command;
	t_list	*spc;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	if (!pre_token)
		cmd->pre_flag = -1;
	command = tokens;
	spc = command->next;
	if (pre_token)
		cmd->pre_flag = get_spc(pre_token);
	cmd->argv = lst_to_arr(command, env_lst);
	cmd->next_flag = get_spc(spc);
	cmd->next = 0;
	return (cmd);
}

void	mini_cmdadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*head;

	if (!(*cmd))
	{
		*cmd = new;
		return ;
	}
	head = *cmd;
	while (head->next)
		head = head->next;
	head->next = new;
	return ;
}

t_cmd   *make_cmd(t_list *tokens, t_lst *env_lst)
{
	t_cmd	*new;
	t_cmd	*cmd;
	t_list	*pre_flag;

	cmd = 0;
	pre_flag = 0;
	while (tokens)
	{
		if (get_spc(tokens) != -1)
		{
			pre_flag = tokens;
			tokens = tokens->next;
		}
		new = mini_cmdnew(tokens, env_lst, pre_flag);
		mini_cmdadd_back(&cmd, new);
		tokens = tokens->next;
	}
	return (cmd);
}