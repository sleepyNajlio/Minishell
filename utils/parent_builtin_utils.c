/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:50:01 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 10:53:53 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_in_files0(t_defcmd *redir, int *flag)
{
	t_redcmd	*tmp;
	int		fd;

	tmp = (t_redcmd *)redir;
	fd = open(tmp->file, tmp->mode);
	if (fd < 0)
	{
		close(fd);
		if (!access(tmp->file, F_OK))
			errors(tmp->file, 10);
		else
			errors(tmp->file, 11);
		*flag = 1;
	}
	close(fd);
}

void	find_in_redir0(t_defcmd *tree, int *flag)
{
	t_redcmd	*tree2;

	if (tree->type == REDIR)
	{
		tree2 = (t_redcmd *)tree;
		find_in_redir0(tree2->cmd, flag);
		if (tree2->fd == 0)
			check_in_files0(tree, flag);
	}
}

void	open_files(t_defcmd *tree, t_env **env_list)
{
	t_redcmd	*tree2;
	int		open_fd;

	tree2 = (t_redcmd *)tree;
	open_fd = open(tree2->file, tree2->mode, 0666);
	if (open_fd < 0)
		return ;
	close(open_fd);
	if (tree2->cmd->type == REDIR)
		open_files(tree2->cmd, env_list);
}

void	parent_builtin_exit(t_defcmd *tree, int *flag)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (!ft_strcmp(cmd->av[0], "exit"))
	{
		ft_exit(cmd);
		*flag = 1;
	}
}

void	parent_builtin_cd(t_defcmd *tree, t_env **env, int *flag)
{
	t_execmd	*cmd;

	cmd = (t_execmd *)tree;
	if (!ft_strcmp(cmd->av[0], "cd"))
	{
		ft_cd(cmd, *env);
		*flag = 1;
	}
}
