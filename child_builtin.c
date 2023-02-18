/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:02:29 by iakry             #+#    #+#             */
/*   Updated: 2023/02/18 23:24:35 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_builtin_cd(t_execmd *tree3, t_env **env_list)
{
	if (!ft_strcmp(tree3->av[0], "cd"))
	{
		my_cd(tree3, *env_list);
		if (errno == 13 || errno == 2)
			exit(1);
		exit(0);
	}
	return (0);
}

int	child_builtin_export(t_execmd *tree3, t_env **env_list)
{
	if (!ft_strcmp(tree3->av[0], "export"))
	{
		ft_export(tree3, env_list);
		if (exit_stat == -6)
			exit(1);
		exit(0);
	}
	return (0);
}

int	child_builtin_unset(t_execmd *tree3, t_env **env_list)
{
	if (!ft_strcmp(tree3->av[0], "unset"))
	{
		my_unset(tree3, env_list);
		if (exit_stat == -6)
			exit(1);
		exit (0);
	}
	return (0);
}

void	child_builtin(t_execmd *tree3, t_env **env_list)
{
	if (empty(tree3->av[0]) == 1)
		exit(0);
	if (!ft_strcmp(tree3->av[0], "exit"))
	{
		my_exit(tree3);
		exit(exit_stat);
	}
	else if (ch_cd(tree3, env_list))
		;
	else if (ch_pwd(tree3->av[0]))
		my_pwd();
	else if (ch_echo(tree3->av[0]))
		my_echo(tree3);
	else if (ch_env(tree3->av[0]))
		my_env_e(tree3, *env_list);
	else if (child_builtin_export(tree3, env_list))
		;
	else if (child_builtin_unset(tree3, env_list))
		;
}
