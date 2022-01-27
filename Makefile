# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkim <tkim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 12:57:28 by tkim              #+#    #+#              #
#    Updated: 2022/01/27 12:57:29 by tkim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LINK = -L/Users/tkim/.brew/Cellar/readline/8.1.1/lib -L./libft/ -lft -lreadline
INCLUDE = -I./libft -I./include -I/Users/tkim/.brew/Cellar/readline/8.1.1/include/
SRC_DIR = ./src/
SRC_NAME = lst_utils.c mini_cd.c mini_echo.c mini_env.c mini_export.c mini_pwd.c mini_unset.c mini_exit.c main.c \
	first_parsing.c set_envp.c path_parsing.c exec_func.c \
	parse_case_quote.c parse_case_doller.c parse_case_none.c parse_case_dquote.c check_quote.c \
	make_argv.c make_cmd.c handle_signal.c memory_free.c print_util.c tokenize.c change_env.c built_in.c \
	handle_redirect.c handle_redirect2.c
SRC = $(addprefix $(SRC_DIR),$(SRC_NAME))
OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a

all: $(NAME)
$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(LINK) $(OBJ) -o $@
$(LIB):
	make -C ./libft/ all
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean:
	rm -f $(OBJ)
	make -C ./libft/ clean
fclean: clean
	rm -f $(NAME)
re: fclean all

