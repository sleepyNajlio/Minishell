/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:20:21 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 05:11:03 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		g_stat = -69;
		tree = line_parsing(env, line);
		exit(0);
	}
	wait(&ex);
	if (WEXITSTATUS(ex))
	{
		g_stat = WEXITSTATUS(ex);
		return (0);
	}
	tree = line_parsing(env, line);
	p_builtin_exec(tree, &err_flag, env);
	master_free(tree);
	if (err_flag)
		return (0);
	return (1);
}
