/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_z.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:00:26 by fel-fil           #+#    #+#             */
/*   Updated: 2023/02/21 00:17:31 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_syntax(char **line_s, char *line_e, int c)
{
	while (!ft_strchr(" \n\t\v\f\r<|>", **line_s) && *line_s < line_e)
	{
		if (**line_s == '\'' || **line_s == '\"')
		{
			c = **line_s;
			(*line_s)++;
			while (**line_s != c && *line_s < line_e)
				(*line_s)++;
			if (*line_s == line_e)
				parsing_err(2);
		}
		if (*line_s != line_e)
			(*line_s)++;
	}
}

void	tok_type(int *type, char **line_s, char *line_e)
{
	if (**line_s == '|')
		(*line_s)++;
	else if (**line_s == '<')
	{
		(*line_s)++;
		if (**line_s == '<')
		{
			(*line_s)++;
			*type = '*';
		}
	}
	else if (**line_s == '>')
	{
		(*line_s)++;
		if (**line_s == '>')
		{
			(*line_s)++;
			*type = '+';
		}
	}
	else
	{
		check_syntax(line_s, line_e, 0);
		*type = 'c';
	}
}

int	tokenizer(char **line_s, char *line_e)
{
	char	*line;
	int		type;

	line = *line_s;
	while (ft_strchr(" \n\t\v\f\r", *line) && line < line_e)
		line++;
	type = *line;
	if (*line == 0)
		return (type);
	tok_type(&type, &line, line_e);
	while (ft_strchr(" \n\t\v\f\r", *line) && line < line_e)
		line++;
	*line_s = line;
	return (type);
}

int	get_tok(char **line_s, char *line_e, char **tok_s, char **tok_e)
{
	char	*line;
	int		type;

	line = *line_s;
	while (ft_strchr(" \n\t\v\f\r", *line) && line < line_e)
		line++;
	if (tok_s)
		*tok_s = line;
	type = *line;
	if (*line == 0)
		return (type);
	tok_type(&type, &line, line_e);
	if (tok_e)
		*tok_e = line;
	while (ft_strchr(" \n\t\v\f\r", *line) && line < line_e)
		line++;
	*line_s = line;
	return (type);
}
