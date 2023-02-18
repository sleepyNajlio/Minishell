#include "minishell.h"

void	child_builtin(t_execmd *tree_e, t_env **my_env)
{
	if (empty(tree_e->av[0]) == 1)
		exit(0);
	if (!ft_strcmp(tree_e->av[0], "exit"))
	{
		ft_exit(tree_e);
		exit(exit_stat);
	}
	else if (ch_cd(tree_e, my_env))
		;
	// else if (ch_pwd(tree_e->av[0]))
	// 	my_pwd();
	// else if (ch_echo(tree_e->av[0]))
	// 	my_echo(tree_e);
	else if (ft_check_for_env(tree_e->av[0]))
		ft_env(tree_e, *my_env);
	else if (child_builtin_export(tree_e, my_env))
		;
	else if (child_builtin_unset(tree_e, my_env))
		;
}
