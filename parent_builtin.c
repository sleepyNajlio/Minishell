/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:41:25 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 10:51:21 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_builtin_unset(t_defcmd *tree, t_env **env, int *flag)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (!ft_strcmp(cmd->av[0], "unset"))
	{
		ft_unset(cmd, env);
		if (g_var == -2)
			g_var = 1;
		else
			g_var = 0;
		*flag = 1;
	}
}

void	parent_builtin_export(t_defcmd *tree, t_env **env, int *flag)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (!ft_strcmp(cmd->av[0], "export") && cmd->av[1])
	{
		ft_export(cmd, env);
		if (g_var == -2)
			g_var = 1;
		else
			g_var = 0;
		*flag = 1;
	}
}

void	execute_builtin(t_defcmd *tree, t_env **env, int *flag)
{
	t_defcmd	*tmp;

	tmp = tree;
	if (tree->type != PIPE)
	{
		find_in_redir0(tmp, flag);
		if (!(*flag))
		{
			tmp = tree;
			if (tree->type == REDIR)
				open_files(tmp, env);
			tmp = tree;
			while (tmp->type != EXEC)
				tmp = ((t_redcmd *)tmp)->cmd;
			parent_builtin_exit(tmp, flag);
			if (!(*flag))
				parent_builtin_cd(tmp, env, flag);
			if (!(*flag))
				parent_builtin_unset(tmp, env, flag);
			if (!(*flag))
				parent_builtin_export(tmp, env, flag);
		}
	}
}

int	parent_builtin(char *line, t_env **env)
{
	t_defcmd	*tree;
	int		id;
	int		exits;
	int		flag;

	flag = 0;
	id = forkk();
	if (id == 0)
	{
		g_var = -100;
		tree = line_parsing(env, line);
		exit(0);
	}
	wait(&exits);
	if (WEXITSTATUS(exits))
	{
		g_var = WEXITSTATUS(exits);
		return (1);
	}
	tree = line_parsing(env, line);
	execute_builtin(tree, env, &flag);
	clean(tree);
	if (flag)
		return (1);
	return (0);
}
