/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 01:51:11 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_in_files(t_defcmd *redir)
{
	t_redcmd	*tmp;
	int		fd;

	tmp = (t_redcmd *)redir;
	fd = open(tmp->file, tmp->mode);
	if (fd < 0)
	{
		close(fd);
		if (!access(tmp->file, F_OK))
			errors(tmp->file, 2);
		else
			errors(tmp->file, 3);
	}
	close(fd);
}

void	find_in_redir(t_defcmd *tree)
{
	t_redcmd	*tree2;

	if (tree->type == REDIR)
	{
		tree2 = (t_redcmd *)tree;
		find_in_redir(tree2->cmd);
		if (tree2->fd == 0)
			check_in_files(tree);
	}
}

void	executor(t_defcmd *tree, int *flag_out, int *flag_in, t_env **env_list)
{
	if (tree->type != PIPE)
		find_in_redir(tree);
	if (tree->type == PIPE)
		ft_pipe(tree, flag_out, flag_in, env_list);
	else if (tree->type == REDIR)
		ft_redir(tree, flag_out, flag_in, env_list);
	else
		ft_execmd(tree, env_list);
}
