/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 01:04:05 by hkhalil           #+#    #+#             */
/*   Updated: 2023/02/18 03:52:24 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir(t_defcmd *tree, int *flag_out, int *flag_in, t_env **env_list)
{
	t_redcmd	*tree2;
	int		open_fd;

	tree2 = (t_redcmd *)tree;
	open_fd = open(tree2->file, tree2->mode, 0666);
	if (open_fd < 0)
		exit(1);
	if ((!(*flag_in) && !(tree2->fd)) || (!(*flag_out) && tree2->fd))
	{
		if (!(tree2->fd))
			*flag_in = 1;
		else
			*flag_out = 1;
		dup2(open_fd, tree2->fd);
	}
	close(open_fd);
	executor(tree2->cmd, flag_out, flag_in, env_list);
}
