#include "../minishell.h"

char	*quotation(char *s)
{
	int		i;
	int		j;
	int		c;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				new[j++] = s[i++];
			if (s[i])
				i++;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = 0;
	free(s);
	return (new);
}

char	*get_str(char *tok_s, char *tok_e)
{
	int		size;
	char	*str;
	int	i;

	i = 0;
	size = tok_e - tok_s;
	str = malloc(tok_e - tok_s + 1);
	if (!str)
		perror("error");
	if (size)
	{
		while (tok_s[i] && i < size)
		{
			str[i] = tok_s[i];
			i++;
		}
		while (i < size)
			str[i++] = 0;
	}
	str[size] = 0;
	return (str);
}

t_defcmd	*heredoc(t_defcmd *cmd, char *s, int tok)
{
	if (exit_stat == -69)
			cmd = construct_red(cmd,
				open_heredoc(quotation(file_expansion(s))),
				O_RDONLY, tok);
	else
		cmd = construct_red(cmd,
				join_free_s2("/tmp/", quotation(file_expansion(s))),
				O_RDONLY, '<');
	return (cmd);
}

t_defcmd	*red_parsing(t_env **env, t_defcmd *tree_head, char **line_s, char *line_e)
{
	int		token;
	char	*tok_s;
	char	*tok_e;
	char	*file_name;
	char	*tok_val;

	token = tokenizer(line_s, line_e);
	if (get_tok(line_s, line_e, &tok_s, &tok_e) != 'c')
		parsing_err(3);
	tok_val = get_str(tok_s, tok_e);
	file_name = str_expansion(tok_val, *env);
	file_name = quotation(file_name);
	if (token == '>')
		tree_head = construct_red(tree_head, file_name, O_WRONLY | O_CREAT | O_TRUNC, token);
	else if (token == '<')
		tree_head = construct_red(tree_head, file_name, O_RDONLY, token);
	else if (token == '+')
		tree_head = construct_red(tree_head, file_name, O_WRONLY | O_CREAT | O_APPEND, token);
	else if (token == '*')
		tree_head = heredoc(tree_head, get_str(tok_s, tok_e), token);
	return (tree_head);
}