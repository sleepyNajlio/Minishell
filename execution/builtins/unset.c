/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:24:04 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/20 20:24:22 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	last_del(t_env *list, t_env *previous)
{
	t_env	*temp;

	temp = list;
	free_env_node(temp);
	previous->next = NULL;
}

void	middle_del(t_env *list, t_env *prev)
{
	t_env	*next;
	t_env	*temp;

	next = list->next;
	temp = list;
	free_env_node(temp);
	prev->next = next;
}

void	first_del(t_env **env, t_env *list)
{
	int		size;
	t_env	*env_t;

	size = ft_lstsize(*env);
	env_t = list;
	if ((*env)->next)
		*env = (*env)->next;
	free(env_t->name);
	free(env_t->value);
	if (size > 1)
		free(env_t);
	if (size == 1)
	{
		*env = NULL;
		list = NULL;
	}
}

void	check_n_delete(t_env **env, char *str)
{
	t_env	*head;
	t_env	*previous;
	int		i;

	i = 0;
	head = *env;
	previous = *env;
	while (head)
	{
		if (ft_strcmp(head->name, str) == 0)
		{
			if (!i)
				first_del(env, head);
			else if (i + 1 == ft_lstsize(*env))
				last_del(head, previous);
			else
				middle_del(head, previous);
			break ;
		}
		previous = head;
		if (head)
			head = head->next;
		i++;
	}
}

void	my_unset(t_execmd *exec, t_env **env)
{
	int	i;

	i = 1;
	while (exec->av[i])
	{
		if (!name_check(exec->av[i]))
		{
			exit_stat = -6;
			printf("unset: `%s': not a valid identifier\n", exec->av[i]);
		}
		else
			check_n_delete(env, exec->av[i]);
		i++;
	}
}
