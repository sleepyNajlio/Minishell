/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:31:28 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/22 01:22:09 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_noargs(t_env **env)
{
	while ((*env))
	{
		if (!(*env)->sep)
			printf("declare -x %s\n", (*env)->name);
		else if (!(*env)->value)
			printf("declare -x %s%c\"\"\n", (*env)->name, (*env)->sep);
		else
			printf("declare -x %s%c\"%s\"\n",
				(*env)->name, (*env)->sep, (*env)->value);
		(*env) = (*env)->next;
	}
	g_stat = 0;
}

void	without_val(t_env **env, char *s, t_env	*addr)
{
	if (exist_check(&addr, 0, s, NULL))
		;
	else if (name_check(s))
	{
		ft_lst_add_back(env,
			ft_lstnew(ft_strdup(s), ft_strdup("\0"), ft_strchar(s, '=')));
	}
	else
	{
		g_stat = -6;
		printf("export: `%s': not a valid identifier\n", s);
	}
}

void	my_export(t_execmd *cmd, t_env **env)
{
	int		i;
	t_env	*addr;

	i = 1;
	if (!cmd->av[i])
		export_noargs(env);
	while (cmd->av[i])
	{
		addr = *env;
		if (ft_strchr(cmd->av[i], '='))
			with_value(env, cmd->av[i], addr);
		else
			without_val(env, cmd->av[i], addr);
		i++;
	}
}
