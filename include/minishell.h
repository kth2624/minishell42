/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkim <tkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:12:43 by tkim              #+#    #+#             */
/*   Updated: 2021/12/16 18:04:15 by seongjki         ###   ########.fr       */
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

typedef struct s_lst
{
	char	*key;
	char	*value;
	struct s_lst *next;
}	t_lst;

int		init_env(t_lst **env_lst, char *envp[]);
t_lst	*split_key_value(char *str);
t_lst	*mini_lstnew(char *key, char *value);
int		mini_lstaddback(t_lst **lst, t_lst *new);
int		mini_lstlen(t_lst *lst);
int		mini_cd(const char *path);
int		mini_pwd(void);
int		mini_env(char *envp[]);
int		mini_export(t_lst **env_lst, char *str);
int		mini_unset(t_lst **env_lst, char *key);
# endif
