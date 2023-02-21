/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:22:44 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 05:38:41 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstnew(void *name, void *val, char sep)
{
	t_env	*env;

	env = malloc(sizeof(*env));
	if (!env)
		return (0);
	env->name = name;
	env->value = val;
	env->sep = sep;
	env->next = NULL;
	return (env);
}

void	ft_lst_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*env_init(char **env)
{
	t_env	*list;
	char	**tmp;
	int		i;

	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		ft_lst_add_back(&list, ft_lstnew(tmp[0], tmp[1], \
			ft_strchar(env[i], '=')));
		free(tmp);
		i++;
	}
	return (list);
}

int	ft_lstsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}
