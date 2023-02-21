/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:25:04 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 00:42:43 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	panic_3(char *name, int flag)
{
	write(2, name, ft_strlen(name));
	if (flag == 2)
		write(2, ": Permission denied\n", 21);
	else
		write(2, ": No such file or directory\n", 29);
	exit(1);
}

void	f_check(t_defcmd *redir)
{
	t_redcmd	*tmp;
	int			fd;

	tmp = (t_redcmd *)redir;
	fd = open(tmp->file, tmp->mode);
	if (fd < 0)
	{
		close(fd);
		if (!access(tmp->file, F_OK))
			panic_3(tmp->file, 2);
		else
			panic_3(tmp->file, 3);
	}
	close(fd);
}

void	r_check(t_defcmd *tree)
{
	t_redcmd	*tree2;

	if (tree->type == REDIR)
	{
		tree2 = (t_redcmd *)tree;
		r_check(tree2->cmd);
		if (tree2->fd == 0)
			f_check(tree);
	}
}

void	execution_time(t_defcmd *tree, int *out, int *in, t_env **my_env)
{
	if (tree->type != PIPE)
		r_check(tree);
	if (tree->type == PIPE)
		exec_pipe(tree, out, in, my_env);
	else if (tree->type == REDIR)
		exec_redir(tree, out, in, my_env);
	else
		exec_cmd(tree, my_env);
}
