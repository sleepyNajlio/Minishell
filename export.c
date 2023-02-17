/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 07:14:38 by hkhalil           #+#    #+#             */
/*   Updated: 2023/02/17 03:47:31 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_exist_add(t_env **env, char **s, int flag)
{
	while (env && *env)
	{
		if (!ft_strcmp((*env)->name, s[0]))
		{
			if (flag && s[1])
			{
				if ((*env)->value)
					free((*env)->value);
				(*env)->value = ft_strdup(s[1]);
			}
			return (1);
		}
		(*env) = (*env)->next;
	}
	return (0);
}

void	global_env(t_env **env, char *s, t_env *addr)
{
	char	**v;

	v = ft_split(s, '=');
	if (v && v[0] && !v[1])
	{
		free(v[1]);
		v[1] = ft_strdup("");
	}
	if (v && v[0] && if_exist_add(&addr, v, 1))
		;
	else
	{
		if (v && v[0] && valid_name(v[0]))
			ft_lst_add_back(env,
				ft_lstnew(ft_strdup(v[0]), ft_strdup(v[1])));
		else
		{
			exit_stat = -2;
			printf("export: `%s': not a valid identifier\n", s);
		}
	}
	free(v[0]);
	free(v[1]);
	free(v);
}

void	local_env(t_env **env, char *s, t_env	*addr)
{
	if (if_exist_add(&addr, &s, 0))
		;
	else if (valid_name(s))
		ft_lst_add_back(env,
			ft_lstnew(ft_strdup(s), NULL));
	else
	{
		exit_stat = -2;
		printf("export: `%s': not a valid identifier\n", s);
	}
}

void	ft_export(t_execmd *cmd, t_env **env)
{
	int			i;
	t_env	*addr;

	i = 1;
	if (!cmd->av[i])
		export_noargs(env);
	while (cmd->av[i])
	{
		addr = *env;
		if (ft_strchr(cmd->av[i], '='))
			global_env(env, cmd->av[i], addr);
		else
			local_env(env, cmd->av[i], addr);
		i++;
	}
}
