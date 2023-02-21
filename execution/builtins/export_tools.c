/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:23:11 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 00:45:07 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_v(char **v)
{
	free(v[0]);
	free(v[1]);
	free(v);
	v = NULL;
}

int	exist_check(t_env **env, char *s, int flag)
{
	char	**v;

	v = ft_split(s, '=');
	while (env && *env)
	{
		if (!ft_strcmp((*env)->name, v[0]))
		{
			if (flag)
			{
				if ((*env)->value)
					free(((*env)->value));
				if (v[1])
					(*env)->value = ft_strdup(v[1]);
				else
					(*env)->value = ft_strdup("");
				(*env)->sep = ft_strchar(s, '=');
			}
			free_v(v);
			return (1);
		}
		(*env) = (*env)->next;
	}
	free_v(v);
	return (0);
}

void	with_value(t_env **env, char *s, t_env *addr)
{
	char	**v;

	v = ft_split(s, '=');
	if (v && v[0] && !v[1])
	{
		free(v[1]);
		v[1] = ft_strdup("");
	}
	if (v && v[0] && exist_check(&addr, s, 1))
		;
	else
	{
		if (v && v[0] && name_check(v[0]))
			ft_lst_add_back(env,
				ft_lstnew(ft_strdup(v[0]),
					ft_strdup(v[1]), ft_strchar(s, '=')));
		else
		{
			g_stat = -6;
			printf("export: `%s': not a valid identifier\n", s);
		}
	}
	free_v(v);
}

void	without_val(t_env **env, char *s, t_env	*addr)
{
	if (exist_check(&addr, s, 0))
		;
	else if (name_check(s))
	{
		ft_lst_add_back(env,
			ft_lstnew(ft_strdup(s), "\0", ft_strchar(s, '=')));
	}
	else
	{
		g_stat = -6;
		printf("export: `%s': not a valid identifier\n", s);
	}
}

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
