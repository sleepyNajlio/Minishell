NAME = minishell

SRC	= export.c child_builtin.c \
	utils/utils1.c utils/utils2.c utils/export_utils.c \
	minishell.c dialna/line_parsing_z.c dialna/constructors_z.c \
	dialna/env_tools_n.c dialna/exe_parsing_z.c dialna/expansion_help_z.c \
	dialna/ft_free_n.c dialna/heredoc_z.c dialna/libft_helper1_z.c \
	dialna/libft_helper2_z.c dialna/libft_helper3_n.c dialna/libft_helper4_n.c \
	dialna/line_parsing_help_z.c dialna/mini_child_n.c dialna/mini_parent_n.c \
	dialna/parent_tools_n.c dialna/parent_tools1_n.c dialna/parsing_err_z.c \
	dialna/pipe_parsing_z.c dialna/red_parsing_z.c dialna/str_expansion_z.c \
	dialna/tokenizer_z.c panic_n.c execution_time_n.c execution_pipe.c \
	execution_red.c execution_exec.c exec_tools.c cd_pwd.c echo_exit.c env_n.c \
	unset_exp_tools.c unset_n.c 

OBJ	= $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g


$(NAME): $(OBJ)
	@$(CC)  $(CFLAGS) $(OBJ) -o $(NAME) -lreadline  -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
	@echo "✅"

all: $(NAME)

clean:
	@rm -rf $(OBJ)
	@echo "🚮"
				
fclean:	clean
	@rm -rf $(NAME)

re:	fclean all
