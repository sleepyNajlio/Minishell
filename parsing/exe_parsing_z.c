#include "../minishell.h"

t_defcmd	*exe_parsing(t_env **env, char **line_s, char *line_e,  int i)
{
	t_defcmd	*tree_head;
	t_execmd	*exe_cmd;
	int		token;
	char	*tok_s;
	char	*tok_e;

	tree_head = construct_exe();
	exe_cmd = (t_execmd *)tree_head;
	while (find("<>", line_s, line_e))
		tree_head = red_parsing(env, tree_head, line_s, line_e);//-
	while (find("|", line_s, line_e) == 0)
	{
		token = get_tok(line_s, line_e, &tok_s, &tok_e);
		if (token == 0)
			break ;
		while (find("<>", line_s, line_e) == 1)
			tree_head = red_parsing(env, tree_head, line_s, line_e);
		if (token != 'c')
			parsing_err(2);
		exe_cmd->av[i] = quotation(str_expansion(get_str(tok_s, tok_e), *env));
		i++;
		if (i >= MAXARGS)
			parsing_err(4);
	}
	exe_cmd->av[i] = 0;
	return (tree_head);
}