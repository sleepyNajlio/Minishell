/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:17:14 by iakry             #+#    #+#             */
/*   Updated: 2022/10/17 09:41:56 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back(t_env **head, t_env *new)
{
	t_env	*temp;

	if (!(*head))
	{
		(*head) = new;
		return ;
	}
	temp = (*head);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_env	*ft_lstadd_new(void *n, void *v)
{
	t_env	*env;

	env = malloc(sizeof(*env));
	if (!env)
		return (NULL);
	env->name = n;
	env->value = v;
	env->next = NULL;
	return (env);
}

t_env	*init_env(char **env)
{
	char		**p;
	int			i;
	t_env	*new;

	new = NULL;
	i = 0;
	printf("\e[1;1H\e[2J");
	while (env[i])
	{
		p = ft_split(env[i], '=');
		ft_lstadd_back(&new, ft_lstadd_new(p[0], p[1]));
		free(p);
		i++;
	}
	return (new);
}
