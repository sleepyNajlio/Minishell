/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 01:14:08 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 20:21:24 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_dir(char *s)
{
	DIR	*dir;

	dir = opendir(s);
	if (dir)
	{
		closedir(dir);
		errors(s, 4);
	}
}

char	*relative_path(t_execmd *tree3, t_env **env_list)
{
	char	*str;
	char	*s;
	int		i;
	char	**path;

	i = -1;
	str = NULL;
	path = envpath(*env_list);
	while (path && path[++i])
	{
		s = join_free_s1(ft_strjoin(path[i], "/"), tree3->av[0]);
		if (access(s, F_OK) != -1)
			str = ft_strdup(s);
		free(s);
	}
	if (!str)
		str = ft_strdup(tree3->av[0]);
	return (str);
}

char	*get_path(t_execmd *tree3, t_env **env_list)
{
	char	*str;

	str = NULL;
	if (ft_strchr(tree3->av[0], '/'))
	{
		if (access(tree3->av[0], F_OK) != -1)
			str = ft_strdup(tree3->av[0]);
		else
			errors(tree3->av[0], 4);
	}
	else
		str = relative_path(tree3, env_list);
	return (str);
}

void	ft_execmd(t_defcmd *tree, t_env **env_list)
{
	t_execmd	*tree3;
	char	*str;

	tree3 = (t_execmd *)tree;
	child_builtin(tree3, env_list);
	check_for_dir(tree3->av[0]);
	str = get_path(tree3, env_list);
	execve(str, tree3->av, list_to_table(*env_list));
	free(str);
	errors(tree3->av[0], 0);
}
