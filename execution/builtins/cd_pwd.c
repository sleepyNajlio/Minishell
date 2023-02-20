/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:25:08 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/20 20:20:31 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ch_cd(t_execmd *tree_e, t_env **my_env)
{
	if (!ft_strcmp(tree_e->av[0], "cd"))
	{
		my_cd(tree_e, *my_env);
		if (errno == 13 || errno == 2)
			exit(1);
		exit(0);
	}
	return (0);
}

void	pwd_update(t_env **env, char *path)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp("PWD", tmp->name))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(path);
			free(path);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lst_add_back(env, ft_lstnew(ft_strdup("PWD"), ft_strdup(path), '='));
	free(path);
}

void	cd_no_arg(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "HOME"))
			chdir(env->value);
		env = env->next;
	}
	exit_stat = 0;
}

void	my_cd(t_execmd *exec, t_env *env)
{
	char	*str;

	if (exec->av[1])
	{
		if (chdir(exec->av[1]))
		{
			write(2, "cd: ", 5);
			perror(exec->av[1]);
			exit_stat = 1;
			return ;
		}
		str = getcwd(NULL, 0);
		if (!str)
		{
			write(2, "cd: error retrieving current directory:\n", 41);
			free(str);
			return ;
		}
		else
			pwd_update(&env, str);
	}
	else
		cd_no_arg(env);
}
