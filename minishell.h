/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:23 by iakry             #+#    #+#             */
/*   Updated: 2022/10/17 18:00:56 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <assert.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>

# define MAXARGS 200
# define PIPE 1
# define REDIR 2
# define EXEC 3

extern int	g_var;

typedef struct s_envvar
{
	char			*name;
	char			*value;
	struct s_envvar	*next;
}	t_env;

typedef struct s_defcmd
{
	int	type;
}	t_defcmd;

typedef struct s_execmd
{
	int		type;
	char	*av[MAXARGS];
}	t_execmd;

typedef struct s_pipecmd
{
	int			type;
	t_defcmd	*left;
	t_defcmd	*right;
}	t_pipecmd;

typedef struct s_redcmd
{
	int		type;
	t_defcmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}	t_redcmd;




t_defcmd	*line_parsing(t_env **env, char *line);
size_t		ft_strlen(const char *s); // --
int			find(char *to_find, char **line_s, char *line_e);
char		*ft_strchr(const char *s, int c);
t_defcmd	*pip_parsing(t_env **env, char **line_s, char *line_e);
int			empty(char *line);
int			is_white_space(int c);
void		parsing_err(int id);
t_defcmd	*construct_pipe(t_defcmd *left, t_defcmd *right);
int			tokenizer(char **line_s, char *line_e);
int			get_tok(char **line_s, char *line_e, char **tok_s, char **tok_e);
t_defcmd	*exe_parsing(t_env **env, char **line_s, char *line_e,  int i);
t_defcmd	*red_parsing(t_env **env, t_defcmd *cmd, char **line_s, char *line_e);
t_defcmd	*construct_red(t_defcmd *cmd_child, char *file_name, int mode, int type);
char		*get_str(char *tok_s, char *tok_e);
char		*str_expansion(char *str, t_env *env);
char		*ft_itoa(int n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
char		*join_free_s1(char const *s1, char const *s2);
char		*ft_env_name(char *s);
t_defcmd	*construct_exe(void);
int			pip_syntax(char *line, int i, int c, int k);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*my_getenv(char *s, t_env *env);
char		*quotation(char *s);
char		*file_expansion(char *arg);
char		*open_heredoc(char *delimiter);
char		*join_free_s1(char const *s1, char const *s2);
char		*join_free_s2(char const *s1, char const *s2);
char		*ft_strdup(const char *str);


//najlio



// libft utils
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin2(char const *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *nptr);
int			ft_tolower(int c);
void		ft_lstadd_back(t_env **head, t_env *new);
t_env	*ft_lstadd_new(void *n, void *v);
int			ft_lstsize(t_env *lst);

//minishell utils
int			forkk(void);
void		errors(char *name, int flag);


char		**list_to_table(t_env *env);
int			valid_name(char *s);

// path
char		**envpath(t_env *env);

// builtins

int			parent_builtin(char *line, t_env **env_list);
void		child_builtin(t_execmd *tree3, t_env **env_list);
int			if_exist_add(t_env **env, char **s, int flag);
t_env	*init_env(char **env);
void		ft_exit(t_execmd *cmd);
void		ft_cd(t_execmd *cmd, t_env *env);
void		ft_pwd(void);
int			ft_check_for_pwd(char *s);
void		ft_echo(t_execmd *cmd);
int			ft_check_for_echo(char *s);
void		ft_env(t_execmd *cmd, t_env *env_list);
int			ft_check_for_env(char *s);
void		ft_export(t_execmd *cmd, t_env **env);
void		ft_unset(t_execmd *cmd, t_env **env);
void		export_noargs(t_env **env);
void		parent_builtin_cd(t_defcmd *tree, t_env **env, int *flag);
void		parent_builtin_exit(t_defcmd *tree, int *flag);
void		open_files(t_defcmd *tree, t_env **env_list);
void		find_in_redir0(t_defcmd *tree, int *flag);
void		check_in_files0(t_defcmd *redir, int *flag);

// executor
void		executor(t_defcmd *tree, int *flag_out,
				int *flag_in, t_env **env_list);
void		parsing_tester(t_defcmd *result_tree);
void		check_in_files(t_defcmd *redir);
void		find_in_redir(t_defcmd *tree);
void		ft_pipe(t_defcmd *tree, int *flag_out,
				int *flag_in, t_env **env_list);
void		ft_redir(t_defcmd *tree, int *flag_out,
				int *flag_in, t_env **env_list);


void		ft_execmd(t_defcmd *tree, t_env **env_list);

//signals
void		handler(int sig);

//readline
void		rl_replace_line(const char *text, int clear_undo);

//free
void		clean(t_defcmd *tree);
void		free_env(t_env **env);
//read
char		*ft_read(t_env **env_list);
//errors
void		errors(char *name, int flag);
#endif
