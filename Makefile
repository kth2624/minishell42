NAME = minishell

#클러스터 경로 : /Users/seongjki/.brew/Cellar/readline/8.1.1
CC = gcc
CFLAGS = -Wall -Wextra
LINK = -L/Users/seongjki/.brew/Cellar/readline/8.1.1/lib -L./libft/ -lft -lreadline
#LINK = -L/opt/homebrew/Cellar/readline/8.1.1/lib/ -L./libft/ -lft -lreadline
INCLUDE = -I./libft -I./include -I/Users/seongjki/.brew/Cellar/readline/8.1.1/include/
#INCLUDE = -I./libft -I./include -I/opt/homebrew/Cellar/readline/8.1.1/include/
SRC_DIR = ./src/
SRC_NAME = lst_utils.c mini_cd.c mini_echo.c mini_env.c mini_export.c mini_pwd.c mini_unset.c mini_exit.c main.c \
	first_parsing.c set_envp.c path_parsing.c exec_func.c \
	parse_case_quote.c parse_case_doller.c parse_case_none.c parse_case_dquote.c check_quote.c \
	make_argv.c make_cmd.c handle_signal.c memory_free.c print_util.c tokenize.c change_env.c built_in.c \
	redirect.c
SRC = $(addprefix $(SRC_DIR),$(SRC_NAME))
OBJ = $(SRC:.c=.o)
TEST_SRC_NAME = lst_utils.c mini_cd.c mini_env.c mini_export.c mini_pwd.c \
mini_unset.c mini_echo.c test.c main.c
TEST_SRC = $(addprefix $(SRC_DIR),$(TEST_SRC_NAME))
TEST_OBJ = $(TEST_SRC:.c=.o)

LIB = ./libft/libft.a

all: $(NAME)
$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(LINK) $(OBJ) -o $@
$(LIB):
	make -C ./libft/ all
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean:
	rm -f $(OBJ) $(TEST_OBJ)
	make -C ./libft/ clean
fclean: clean
	rm -f $(NAME) test
re: fclean all

