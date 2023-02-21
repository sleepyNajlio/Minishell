/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:22:54 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 05:38:55 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	panic_env(char *s)
{
	printf("env: %s: No such file or directory\n", s);
	exit(127);
}

int	ch_env(char *s)
{
	if (ft_strlen(s) != 3)
		return (0);
	if (ft_tolower(s[0]) == 'e'
		&& ft_tolower(s[1]) == 'n' && ft_tolower(s[2]) == 'v')
		return (1);
	return (0);
}

void	my_env_e(t_execmd *exec, t_env *env)
{
	if (exec->av[1])
		panic_env(exec->av[1]);
	else
	{
		while (env)
		{
			if (env->value && env->sep == '=')
				printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
	exit(0);
}
