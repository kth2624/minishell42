/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:12:43 by tkim              #+#    #+#             */
/*   Updated: 2022/01/05 16:57:29 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_lst
{
	char			*key;
	char			*value;
	int				idx;
	struct s_lst	*next;
}	t_lst;

/* set_envp.c */
int		init_env_lst(t_lst **env_lst, char *envp[]);
t_lst	*split_key_value(char *str, int lst_idx);
char	**make_env_arr(t_lst *env_lst);
/* lst_utils.c */
t_lst	*mini_lstnew(char *key, char *value, int idx);
int		mini_lstaddback(t_lst **lst, t_lst *new);
int		mini_lstlen(t_lst *lst);
/* built_in_func */
int		mini_echo(char *argv[], int flag);
int		mini_cd(char *argv[]);
int		mini_pwd(void);
int		mini_env(t_lst *env_lst);
int		mini_export(t_lst **env_lst, char *argv[]);
int		mini_unset(t_lst **env_lst, char *argv[]);
/* first_parsing.c*/
t_list	*first_parsing(char *input);
/* path_parsing.c*/
char	**path_parsing(char *arg, t_lst *env_lst);
/* exec_func.c*/
int		exec_path(char **path_arr, char *argv[], char *env_arr[]);
int		exec_built_in_func(char *argv[], t_lst **env_lst);

int	cnt_quote_len(char *input, int *idx);
int	cnt_doller_len(char *input, int *idx);
//int	cnt_none_len(char *input, int idx);
//int	cnt_dquote_len(char *input, int *idx);
char *replace_doller(char *arg, t_lst *env_lst);
int	is_mini_printable(char c);

char *parse_case_none(char *input, int *i, t_lst *env_lst);
char *parse_case_quote(char *input, int *i);
char *parse_case_dquote(char *input, int *i, t_lst *env_lst);
char *parse_case_doller(char *input, int *i, t_lst *env_lst);

int	is_valid_quote(char *input);


#endif
