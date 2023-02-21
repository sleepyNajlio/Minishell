/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_help_z.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:48:27 by fel-fil           #+#    #+#             */
/*   Updated: 2023/02/21 00:17:08 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env_name(int c)
{
	if (c == '$')
		return (0);
	else if (is_white_space(c))
		return (0);
	else if (c == '\'')
		return (0);
	else if (c == '\"')
		return (0);
	else if (c == 0)
		return (0);
	else
		return (1);
}

char	*get_env_name(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while ((str[i] == '_' || ft_isalpha(str[i]) || ft_isdigit(str[i]))
		&& check_env_name(str[i]))
		i++;
	ret = ft_substr(str, 0, i);
	return (ret);
}

char	*my_getenv(char *env_name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, env_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (0);
}

char	*file_expansion(char *arg)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1]
			&& (arg[i + 1] == '\'' || arg[i + 1] == '\"'))
		{
			new_arg = join_free_s1(ft_substr(arg, 0, i), &arg[i + 1]);
			free(arg);
			arg = ft_strdup(new_arg);
			free(new_arg);
		}
		i++;
	}
	return (arg);
}

void	found_env(char **str, int *i, t_env *env, char *c)
{
	char	*s;
	char	*after_exp;

	s = ft_strdup(my_getenv(c, env));
	after_exp = join_free_s1(ft_substr(*str, 0, *i), s);
	after_exp = join_free_s1(after_exp, &(*str)[*i + ft_strlen(c) + 1]);
	free(*str);
	*str = ft_strdup(after_exp);
	free(after_exp);
	*i = *i + ft_strlen(s);
	free(s);
}
