/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:12:43 by tkim              #+#    #+#             */
/*   Updated: 2022/01/27 12:57:49 by tkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>

# define PIPE 0
# define REDIRECT1 1
# define REDIRECT2 2
# define REDIRECT3 3
# define REDIRECT4 4
# define WORD -1
# define FILE -2

int	g_status;

typedef struct s_lst
{
	char			*key;
	char			*value;
	int				idx;
	struct s_lst	*next;
}	t_lst;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	int				pipe[2];
	int				fd_in;
	int				fd_out;
	int				is_pipe;
	struct s_cmd	*next;
}	t_cmd;

/* set_envp.c */
int		init_env_lst(t_lst **env_lst, char *envp[]);
t_lst	*split_key_value(char *str, int lst_idx);
char	**make_env_arr(t_lst *env_lst);
/* lst_utils.c */
t_lst	*mini_lstnew(char *key, char *value, int idx);
int		mini_lstaddback(t_lst **lst, t_lst *new);
int		mini_lstlen(t_lst *lst);
int		mini_tokenadd_back(t_token **lst, t_token *new);
t_token	*mini_tokennew(char *content);
/* built_in_func */
int		mini_echo(char *argv[], int flag);
int		mini_cd(char *argv[], t_lst *env_lst);
int		mini_pwd(void);
int		mini_env(t_lst *env_lst);
int		mini_export(t_lst **env_lst, char *argv[]);
int		mini_unset(t_lst **env_lst, char *argv[]);
int		mini_exit(char *argv[]);
/* first_parsing.c*/
t_cmd	*first_parsing(char *input, t_lst *env_lst);
/* path_parsing.c*/
char	**path_parsing(char *arg, t_lst *env_lst);
char	*path_is_valid(char *arg, char **path_arr);
/* exec_func.c*/
void	exec_path(t_cmd *cmd, t_cmd *prev, char **env_arr, char **path_arr);
void	set_g_status(void);
/*built_in.c*/
int		exec_built_in_func(char *argv[], t_lst **env_lst);
int		is_built_in(char *argv[]);
void	exec_built_in(t_cmd *cmd, t_lst **env_lst, t_cmd *prev);
/*redirect.c*/
void	check_redirection(t_token *tokens, int *fd_in, int *fd_out);
void	set_redirect_and_pipe(t_cmd *cmd, t_cmd *prev);
/* memory_free.c*/
void	free_2dim_arr(char **str);
void	free_token(t_token *tokens);
void	free_cmd(t_cmd *cmd);
void	free_env_lst(t_lst *env_lst);
int		cnt_doller_len(char *input, int *idx);
char	*replace_doller(char *arg, t_lst *env_lst);
int		is_mini_printable(char c);
char	*mini_strjoin(char *s1, char *s2, int idx, int r_idx);
char	*parse_case_none(char *input, int *i, t_lst *env_lst);
char	*parse_case_quote(char *input, int *i);
char	*parse_case_dquote(char *input, int *i, t_lst *env_lst);
char	*parse_case_doller(char *input, int *i, t_lst *env_lst);
int		is_valid_quote(char *input);
/*make_argv.c*/
char	**make_argv(t_token *token);
/*make_cmd.c*/
t_cmd	*make_cmd(t_token *tokens);
/*handle_signal.c*/
int		handle_signal(void);
void	handle_signal_child(void);
/*print_util.c*/
void	print_token(t_token *tokens);
void	print_cmd(t_cmd *cmd);
void	print_2dim_arr(char **arr);
/*tokenize.c*/
t_token	*tokenize(char *input);
void	fill_token_type(t_token *tokens);
/*change_env.c*/
void	convert_content(t_token **tokens, t_lst *env_lst);
void	close_fd(t_cmd *cmd);

#endif