/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing_z.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:52:00 by fel-fil           #+#    #+#             */
/*   Updated: 2023/02/21 00:06:59 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*end_line(char *line)
{
	char	*ret;

	ret = line + ft_strlen(line);
	return (ret);
}

t_defcmd	*line_parsing(t_env **env, char *line)
{
	char	*end_s;

	end_s = end_line(line);
	return (pip_parsing(env, &line, end_s));
}
