/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:24:34 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 00:45:07 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ch_unset(t_execmd *tree_e, t_env **my_env)
{
	if (!ft_strcmp(tree_e->av[0], "unset"))
	{
		my_unset(tree_e, my_env);
		if (g_stat == -6)
			exit(1);
		exit (0);
	}
	return (0);
}

int	ch_export(t_execmd *tree_e, t_env **my_env)
{
	if (!ft_strcmp(tree_e->av[0], "export"))
	{
		my_export(tree_e, my_env);
		if (g_stat == -6)
			exit(1);
		exit(0);
	}
	return (0);
}

void	child_builtin(t_execmd *tree_e, t_env **my_env)
{
	if (empty(tree_e->av[0]) == 1)
		exit(0);
	if (ft_strcmp(tree_e->av[0], "exit") == 0)
	{
		my_exit(tree_e);
		exit(g_stat);
	}
	else if (ch_env(tree_e->av[0]))
		my_env_e(tree_e, *my_env);
	else if (ch_pwd(tree_e->av[0]))
		my_pwd();
	else if (ch_cd(tree_e, my_env))
		;
	else if (ch_echo(tree_e->av[0]))
		my_echo(tree_e);
	else if (ch_unset(tree_e, my_env))
		;
	else if (ch_export(tree_e, my_env))
		;
}
