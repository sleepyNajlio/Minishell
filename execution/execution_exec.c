/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:24:43 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 00:42:16 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_directory(char *s)
{
	DIR	*dir;

	if (ft_strchr(s, '/'))
	{
		if (access(s, F_OK) == 0)
		{
			dir = opendir(s);
			if (dir)
			{
				closedir(dir);
				panic(s, 4);
			}
		}
	}
}

char	**envpath(t_env *env)
{
	char	**path;

	path = NULL;
	while (env)
	{
		if (!ft_strcmp(env->name, "PATH"))
			path = ft_split(env->value, ':');
		env = env->next;
	}
	return (path);
}

char	*ft_rel_path(t_execmd *tree_e, t_env **my_env)
{
	char	*path;
	char	*s;
	int		i;
	char	**paths;

	i = -1;
	path = NULL;
	paths = envpath(*my_env);
	while (paths && paths[++i])
	{
		s = join_free_s1(ft_strjoin(paths[i], "/"), tree_e->av[0]);
		if (access(s, F_OK) != -1)
			path = ft_strdup(s);
		free(s);
	}
	if (!path)
		path = ft_strdup(tree_e->av[0]);
	return (path);
}

char	*ft_path(t_execmd *tree_e, t_env **my_env)
{
	char	*path;

	path = NULL;
	if (ft_strchr(tree_e->av[0], '/'))
	{
		if (access(tree_e->av[0], F_OK) != -1)
			path = ft_strdup(tree_e->av[0]);
		else
			panic(tree_e->av[0], 4);
	}
	else
		path = ft_rel_path(tree_e, my_env);
	return (path);
}

void	exec_cmd(t_defcmd *tree, t_env **my_env)
{
	t_execmd	*tree_e;
	char		*str;

	tree_e = (t_execmd *)tree;
	child_builtin(tree_e, my_env);
	check_directory(tree_e->av[0]);
	str = ft_path(tree_e, my_env);
	execve(str, tree_e->av, env_tab(*my_env));
	free(str);
	panic(tree_e->av[0], 0);
}
