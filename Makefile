NAME = minishell

SRC	=  parent_builtin.c export.c unset.c env.c pwd.c cd.c echo.c exit.c exec.c redir.c pipe.c utils/env_utils.c child_builtin.c clean.c errors.c executor.c main.c path.c\
	utils/libft/utils0.c utils/libft/utils1.c utils/libft/utils2.c utils/libft/utils3.c utils/libft/utils4.c utils/utils0.c utils/utils1.c utils/utils2.c utils/export_utils.c utils/parent_builtin_utils.c\
	line_parsing_z.c line_parsing_help_z.c pipe_parsing_z.c parsing_err_z.c constructors_z.c tokenizer_z.c exe_parsing_z.c red_parsing_z.c str_expansion_z.c libft_helper1_z.c libft_helper2_z.c expansion_help_z.c\
	heredoc_z.c

OBJ	= $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g


$(NAME): $(OBJ)
	$(CC)  $(CFLAGS) $(OBJ) -o $(NAME) -lreadline  -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

all: $(NAME)

clean:
	rm -rf $(OBJ)
				
fclean:	clean
	rm -rf $(NAME)

re:	fclean all
