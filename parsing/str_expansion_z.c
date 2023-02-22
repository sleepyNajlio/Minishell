/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expansion_z.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:00:16 by fel-fil           #+#    #+#             */
/*   Updated: 2023/02/22 00:42:52 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_exp(char **str, int *i)
{
	char	*exit_val;
	char	*after_exp;

	if (g_stat == 23)
		g_stat = 258;
	exit_val = ft_itoa(g_stat);
	after_exp = join_free_s1(ft_substr(*str, 0, *i), exit_val);
	after_exp = join_free_s1(after_exp, &(*str)[*i + 2]);
	free(*str);
	*str = ft_strdup(after_exp);
	free(exit_val);
	free(after_exp);
	(*i)++;
}

void	env_exp(char **str, int *i, t_env *env)
{
	char	*after_exp;
	char	*env_name;

	env_name = get_env_name(&(*str)[*i + 1]);
	if (my_getenv(env_name, env))
		found_env(str, i, env, env_name);
	else if ((*str)[*i + 1] && ((*str)[*i + 1] == '\''
				|| (*str)[*i + 1] == '\"'))
	{
		after_exp = join_free_s1(ft_substr(*str, 0, *i), &(*str)[*i + 1]);
		free(*str);
		*str = ft_strdup(after_exp);
		free(after_exp);
	}
	else if (env_name[0])
	{
		after_exp = join_free_s1(ft_substr(*str, 0, *i),
				&(*str)[*i + ft_strlen(env_name) + 1]);
		free(*str);
		*str = ft_strdup(after_exp);
		free(after_exp);
	}
	else
		(*i)++;
	free(env_name);
}

void	expansion(char **str, int *i, t_env *env)
{
	if ((*str)[*i + 1] == '?')
		exit_exp(str, i);
	else
		env_exp(str, i, env);
}

char	*str_expansion(char *str, t_env *env)
{
	int	i;
	int	is_quote;

	i = 0;
	is_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (is_quote == 0)
				is_quote = str[i];
			else if (str[i] == is_quote)
				is_quote = 0;
		}
		if (str[i] == '$' && is_quote != '\'')
			expansion(&str, &i, env);
		else
			i++;
	}
	return (str);
}
