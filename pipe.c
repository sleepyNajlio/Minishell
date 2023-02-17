/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:22:59 by hkhalil           #+#    #+#             */
/*   Updated: 2023/02/17 04:09:51 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(int p[2])
{
	if (pipe(p) < 0)
		perror("pipe error");
}

void	ft_wait(int id)
{
	int	last;
	int	mid;

	waitpid(id, &last, 0);
	while (wait(&mid) > 0)
	{
		if ((WTERMSIG(mid) == 3 || WTERMSIG(mid) == 2)
			&& (WTERMSIG(last) != 3 && WTERMSIG(last) != 2))
		exit_stat = -1;
	}
	exit(WEXITSTATUS(last));
}

void	ft_pipe(t_defcmd *tree, int *flag_out, int *flag_in, t_env **env_list)
{
	t_pipecmd	*tree1;
	int		p[2];
	int		id;

	tree1 = (t_pipecmd *)tree;
	create_pipe(p);
	id = my_fork();
	if (id == 0)
	{
		close(p[0]);
		dup2(p[1], 1);
		close(p[1]);
		executor(tree1->left, flag_out, flag_in, env_list);
	}
	id = my_fork();
	if (id == 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		executor(tree1->right, flag_out, flag_in, env_list);
	}
	close(p[0]);
	close(p[1]);
	ft_wait(id);
}
