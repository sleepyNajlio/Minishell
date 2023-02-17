/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:07:20 by iakry             #+#    #+#             */
/*   Updated: 2022/10/15 21:09:27 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
