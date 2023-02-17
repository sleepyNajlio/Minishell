/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 04:32:05 by hkhalil           #+#    #+#             */
/*   Updated: 2023/02/17 03:47:31 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_env **env, char *path)
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
	ft_lst_add_back(env, ft_lstnew(ft_strdup("PWD"), ft_strdup(path)));
	free(path);
}

void	ft_cd(t_execmd *cmd, t_env *env)
{
	if (cmd->av[1])
	{
		if (chdir(cmd->av[1]))
		{
			write(2, "cd: ", 5);
			perror(cmd->av[1]);
			exit_stat = 1;
			return ;
		}
		update_pwd(&env, getcwd(NULL, 0));
	}
	if (!(cmd->av[1]))
	{
		while (env)
		{
			if (!ft_strcmp(env->name, "HOME"))
				chdir(env->value);
			env = env->next;
		}
		exit_stat = 0;
	}
}
