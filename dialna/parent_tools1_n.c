#include "../minishell.h"

void	exit_parent(t_defcmd *tree, int *done)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (ft_strcmp(cmd->av[0], "exit") == 0)
	{
		*done = 1;
		my_exit(cmd);
	}
}

void	cd_parent(t_defcmd *tree, int *done, t_env **env)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (ft_strcmp(cmd->av[0], "cd") == 0)
	{
		*done = 1;
		my_cd(cmd, *env);
	}
}

void	unset_parent(t_defcmd *tree, int *done, t_env **env)
{
	t_execmd	*command;

	command = (t_execmd *)tree;
	if (ft_strcmp(command->av[0], "unset") == 0)
	{
		my_unset(command, env);
		if (exit_stat == -6)
			exit_stat = 1;
		else
			exit_stat = 0;
		*done = 1;
	}
}

void	export_parent(t_defcmd *tree, int *done, t_env **env)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (ft_strcmp(cmd->av[0], "export") == 0 && cmd->av[1])
	{
		ft_export(cmd, env);
		if (exit_stat == -6)
			exit_stat = 1;
		else
			exit_stat = 0;
		*done = 1;
	}
}
