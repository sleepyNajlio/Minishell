#include "../minishell.h"

int	mini_parent(char *line, t_env **env)
{
	int			pid;
	int			ex;
	int			err_flag;
	t_defcmd	*tree;

	err_flag = 0;
	pid = my_fork();
	if (pid == 0)
	{
		exit_stat = -69;
		tree = line_parsing(env, line);
		exit(0);
	}
	wait(&ex);
	if (WEXITSTATUS(ex))
	{
		exit_stat = WEXITSTATUS(ex);
		return (0);
	}
	tree = line_parsing(env, line);
	p_builtin_exec(tree, &err_flag, env);
	master_free(tree);
	if (err_flag)
		return (0);
	return (1);
}
