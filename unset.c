/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 05:24:09 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 21:12:15 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_first(t_env **env, t_env *list)
{
	t_env	*tmp;
	int			n;

	n = ft_lstsize(*env);
	tmp = list;
	if ((*env)->next)
		*env = (*env)->next;
	free(tmp->name);
	free(tmp->value);
	if (n > 1)
		free(tmp);
	if (n == 1)
	{
		*env = NULL;
		list = NULL;
	}
}

void	remove_last(t_env *list, t_env *prev)
{
	t_env	*tmp;

	tmp = list;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	prev->next = NULL;
}

void	remove_mid(t_env *list, t_env *prev)
{
	t_env	*tmp;
	t_env	*next;

	tmp = list;
	next = list->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	prev->next = next;
}

void	if_exist_delete(t_env **env, char *s)
{
	t_env	*prev;
	t_env	*list;
	int			i;

	prev = *env;
	list = *env;
	i = 0;
	while (list)
	{
		if (!ft_strcmp(list->name, s))
		{
			if (i == 0)
				remove_first(env, list);
			else if (i + 1 == ft_lstsize(*env))
				remove_last(list, prev);
			else
				remove_mid(list, prev);
			break ;
		}
		prev = list;
		if (list)
			list = list->next;
		i++;
	}
}

void	ft_unset(t_execmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd->av[i])
	{
		if (!valid_name(cmd->av[i]))
		{
			g_var = -2;
			printf("unset: `%s': not a valid identifier\n", cmd->av[i]);
		}
		else
			if_exist_delete(env, cmd->av[i]);
		i++;
	}
}
