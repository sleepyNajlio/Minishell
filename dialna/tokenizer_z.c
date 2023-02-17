#include "../minishell.h"

void	check_syntax(char **s, char *es, int c)
{
	while (!ft_strchr(" \n\t\v\f\r<|>", **s) && *s < es)
	{
		if (**s == '\'' || **s == '\"')
		{
			c = **s;
			(*s)++;
			while (**s != c && *s < es)
				(*s)++;
			if (*s == es)
				parsing_err(2);
		}
		if (*s != es)
			(*s)++;
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
