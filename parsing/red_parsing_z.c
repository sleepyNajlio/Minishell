/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parsing_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:14:58 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 04:47:53 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quotation(char *str)
{
	int		i;
	int		k;
	int		c;
	char	*ret;

	i = 0;
	k = 0;
	ret = malloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				ret[k++] = str[i++];
			if (str[i])
				i++;
		}
		else
			ret[k++] = str[i++];
	}
	free(str);
	ret[k] = 0;
	return (ret);
}

char	*get_str(char *tok_s, char *tok_e)
{
	int		size;
	char	*str;
	int		i;

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
	char	*hd;

	if (g_stat == -69)
	{
		hd = open_heredoc(quotation(file_expansion(s)));
		cmd = construct_red(cmd,hd, O_RDONLY, tok);
	}
	else
	{
		cmd = construct_red(cmd,
				join_free_s2("/tmp/", quotation(file_expansion(s))),
				O_RDONLY, '<');
	}
	return (cmd);
}

t_defcmd	*red_parsing(t_env **env, t_defcmd *tree_head, char **l_s, char *le)
{
	int		token;
	char	*tok_s;
	char	*tok_e;
	char	*file_name;
	char	*tok_val;

	token = tokenizer(l_s, le);
	if (get_tok(l_s, le, &tok_s, &tok_e) != 'c')
		parsing_err(3);
	tok_val = get_str(tok_s, tok_e);
	file_name = str_expansion(tok_val, *env);
	file_name = strdup(file_name);
	free(tok_val);
	tok_val = NULL;
	file_name = quotation(file_name);
	if (token == '*')
		tree_head = heredoc(tree_head, get_str(tok_s, tok_e), token);
	else if (token == '<')
		tree_head = construct_red(tree_head, file_name, O_RDONLY, token);
	else if (token == '+')
		tree_head = construct_red(tree_head, file_name,
				O_WRONLY | O_CREAT | O_APPEND, token);
	else if (token == '>')
		tree_head = construct_red(tree_head, file_name,
				O_WRONLY | O_CREAT | O_TRUNC, token);
	//free(file_name);
	return (tree_head);
}
