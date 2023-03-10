CPPFLAGS = -I/Users/nloutfi/.brew/Cellar/readline/8.2.1/include
LDFLAGS = -L/Users/nloutfi/.brew/Cellar/readline/8.2.1/lib

# LDFLAGS="-L/opt/homebrew/opt/readline/lib"
# CPPFLAGS="-I/opt/homebrew/opt/readline/include"


NAME = minishell
CC = cc

SANITIZE = -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
		
SRC = minishell.c parsing/constructors_z.c parsing/exe_parsing_z.c parsing/expansion_help_z.c parsing/heredoc_z.c parsing/libft_helper1_z.c \
	parsing/libft_helper2_z.c parsing/line_parsing_help_z.c parsing/line_parsing_z.c parsing/parsing_err_z.c parsing/pipe_parsing_z.c parsing/red_parsing_z.c \
	parsing/str_expansion_z.c parsing/tokenizer_z.c execution/exec_tools.c execution/execution_exec.c execution/execution_pipe.c execution/execution_red.c\
	execution/execution_time.c execution/panic.c execution/builtins/builtins_child.c execution/builtins/builtins_parent.c execution/builtins/cd_pwd.c \
	execution/builtins/echo_exit.c execution/builtins/env.c execution/builtins/env_tools.c execution/builtins/export.c execution/builtins/ft_free.c \
	execution/builtins/parent_tools.c execution/builtins/parent_tools1.c execution/builtins/pwd.c execution/builtins/unset.c execution/builtins/unset_exp_tools.c \
	execution/libft_helper3.c execution/libft_helper4.c  -g3 execution/mini_child.c execution/builtins/export_tools.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME):
	@$(CC) $(CPPFLAGS) $(SRC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -lreadline  -o $(NAME)
	@echo "👍👍👍"

clean :
	@rm -f $(OBJ)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all