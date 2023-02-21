/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing_help_z.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:51:36 by fel-fil           #+#    #+#             */
/*   Updated: 2023/02/21 00:43:50 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char)c;
	while (*s != '\0' && c != *s)
		s++;
	if (c == *s)
		return ((char *)s);
	return (0);
}

int	find(char *to_find, char **line_s, char *line_e)
{
	char	*s;

	s = *line_s;
	while (ft_strchr(" \n\t\v\f\r", *s) && s < line_e)
		s++;
	*line_s = s;
	if (*s && ft_strchr(to_find, *s))
		return (1);
	else
		return (0);
}

char	ft_strchar(const char *s, int c)
{
	c = (char)c;
	while (*s != '\0' && c != *s)
		s++;
	if (c == *s)
		return (*s);
	return (0);
}
