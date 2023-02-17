/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 04:32:05 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 19:09:13 by hkhalil          ###   ########.fr       */
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
	ft_lstadd_back(env, ft_lstadd_new(ft_strdup("PWD"), ft_strdup(path)));
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
			g_var = 1;
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
		g_var = 0;
	}
}
