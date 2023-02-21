/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors_z.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:43:34 by fel-fil           #+#    #+#             */
/*   Updated: 2023/02/20 23:54:16 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_defcmd	*construct_pipe(t_defcmd *left, t_defcmd *right)
{
	t_pipecmd	*pipecmd;
	t_defcmd	*ret;

	pipecmd = malloc(sizeof(*pipecmd));
	pipecmd->left = left;
	pipecmd->right = right;
	pipecmd->type = PIPE;
	ret = (t_defcmd *)pipecmd;
	return (ret);
}

t_defcmd	*construct_exe(void)
{
	t_execmd	*execmd;
	t_defcmd	*ret;

	execmd = malloc(sizeof(*execmd));
	execmd->type = EXEC;
	ret = (t_defcmd *)execmd;
	return (ret);
}

t_defcmd	*construct_red(t_defcmd *cmd_child, char *file_name, int m, int t)
{
	t_redcmd	*redcmd;
	t_defcmd	*ret;

	redcmd = malloc(sizeof(*redcmd));
	redcmd->cmd = cmd_child;
	redcmd->file = file_name;
	redcmd->mode = m;
	if (t == '<' || t == '*')
		redcmd->fd = 0;
	else
		redcmd->fd = 1;
	redcmd->type = REDIR;
	ret = (t_defcmd *)redcmd;
	return (ret);
}
