/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:52:42 by hkhalil           #+#    #+#             */
/*   Updated: 2023/02/19 02:34:48 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	greater_than_min(t_env **env, char **min, char *c)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, c) > 0)
		{
			free(min[0]);
			free(min[1]);
			min[0] = ft_strdup(tmp->name);
			min[1] = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	new_min(t_env **env, char **min, char *c)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if ((ft_strcmp(min[0], tmp->name) > 0) && (ft_strcmp(tmp->name, c) > 0))
		{
			free(min[0]);
			free(min[1]);
			min[0] = ft_strdup(tmp->name);
			min[1] = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
}

// void	ft_print(char **min, char **c)
// {
// 	if (min[1] && min[2][0] == '=')
// 		printf("declare -x %s=\"%s\"\n", min[0], min[1]);
// 	else
// 		printf("declare -x %s\n", min[0]);
// 	free(*c);
// 	*c = ft_strdup(min[0]);
// }

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
	exit_stat = 0;
}
