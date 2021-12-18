# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 15:34:07 by seongjki          #+#    #+#              #
#    Updated: 2021/12/18 14:20:27 by seongjki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra
LINK = -lreadline -L./libft/ -lft
INCLUDE = -I./libft -I./include

SRC_DIR = ./src/
SRC_NAME = lst_utils.c mini_cd.c mini_env.c mini_export.c mini_pwd.c mini_unset.c main.c
SRC = $(addprefix $(SRC_DIR),$(SRC_NAME))
OBJ = $(SRC:.c=.o)
TEST_SRC_NAME = lst_utils.c mini_cd.c mini_env.c mini_export.c mini_pwd.c \
mini_unset.c mini_echo.c test.c main.c
TEST_SRC = $(addprefix $(SRC_DIR),$(TEST_SRC_NAME))
TEST_OBJ = $(TEST_SRC:.c=.o)

LIB = ./libft/libft.a

all: $(NAME)
$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(LINK) $(OBJ) -o $@
$(LIB):
	make -C ./libft/ all
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

test: $(LIB) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(LINK) $(TEST_OBJ) -o $@
clean:
	rm -f $(OBJ)
	make -C ./libft/ clean
fclean: clean
	rm -f $(NAME) test
re: fclean all

