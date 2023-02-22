/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:23:11 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/22 01:26:51 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exist_check(t_env **env, int flag, char *name, char *value)
{
	while (env && *env)
	{
		if (!ft_strcmp((*env)->name, name))
		{
			if (flag)
			{
				if ((*env)->value)
					free(((*env)->value));
				if (value)
					(*env)->value = ft_strdup(value);
				else
					(*env)->value = ft_strdup("");
				(*env)->sep = '=';
			}
			return (1);
		}
		(*env) = (*env)->next;
	}
	return (0);
}

char	*ft_name(char *s)
{
	int		i;
	char	*name;

	i = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*ft_value(char *s)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (s && s[i] && s[i] != '=')
		i++;
	value = malloc(sizeof(char) * ft_strlen(s) - i);
	i++;
	while (s[i])
		value[j++] = s[i++];
	value[j] = '\0';
	return (value);
}

void	free_val(char *value)
{
	free(value);
	value = ft_strdup("");
}

void	with_value(t_env **env, char *s, t_env *addr)
{
	char	*name;
	char	*value;

	name = ft_name(s);
	value = ft_value(s);
	if (name && !value)
		free_val(value);
	if (name && exist_check(&addr, 1, name, value))
		;
	else
	{
		if (name && name_check(name))
			ft_lst_add_back(env,
				ft_lstnew(ft_strdup(name),
					ft_strdup(value), ft_strchar(s, '=')));
		else
		{
			g_stat = -6;
			printf("export: `%s': not a valid identifier\n", s);
		}
	}
	free(name);
	free(value);
}
