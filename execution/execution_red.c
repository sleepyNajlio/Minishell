/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:24:55 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/20 20:25:01 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	files_check9(t_defcmd *redir, int fd)
{
	t_redcmd	*tmp;

	tmp = (t_redcmd *)redir;
	if (fd < 0)
	{
		close(fd);
		if (access(tmp->file, F_OK) == 0)
			panic_1(tmp->file, 1);
		else
			panic_1(tmp->file, 0);
	}
	close(fd);
	exit(1);
}

void	exec_redir(t_defcmd *tree, int *out, int *in, t_env **my_env)
{
	t_redcmd	*tree_r;
	int			fd;

	tree_r = (t_redcmd *)tree;
	fd = open(tree_r->file, tree_r->mode, 0666);
	if (fd < 0)
		files_check9(tree, fd);
	if ((!(*in) && !(tree_r->fd)) || (!(*out) && tree_r->fd))
	{
		if (!(tree_r->fd))
			*in = 1;
		else
			*out = 1;
		dup2(fd, tree_r->fd);
	}
	close(fd);
	execution_time(tree_r->cmd, out, in, my_env);
}