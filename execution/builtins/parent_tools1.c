/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_tools1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:23:28 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 00:45:07 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		my_cd(cmd, *env);
		*done = 1;
	}
}

void	unset_parent(t_defcmd *tree, int *done, t_env **env)
{
	t_execmd	*command;

	command = (t_execmd *)tree;
	if (ft_strcmp(command->av[0], "unset") == 0)
	{
		my_unset(command, env);
		if (g_stat == -6)
			g_stat = 1;
		else
			g_stat = 0;
		*done = 1;
	}
}

void	export_parent(t_defcmd *tree, int *done, t_env **env)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (ft_strcmp(cmd->av[0], "export") == 0 && cmd->av[1])
	{
		my_export(cmd, env);
		if (g_stat == -6)
			g_stat = 1;
		else
			g_stat = 0;
		*done = 1;
	}
}
