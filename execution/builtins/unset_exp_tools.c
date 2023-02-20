/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exp_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:23:52 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/20 20:23:55 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	name_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
	{
		exit_stat = -6;
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
		{
			exit_stat = -6;
			return (0);
		}
		i++;
	}
	return (1);
}

void    free_env_node(t_env *env)
{
    free(env->name);
    free(env->value);
    free(env);
}