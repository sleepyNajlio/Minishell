#include "../minishell.h"


int	is_white_space(int c)
{
	if (c == ' ' || c == '\n' || c == '\v'
		|| c == '\t' || c == '\f' || c == '\r')
		return (1);
	return (0);
}



int	pip_syntax(char *line, int i, int c, int k)
{
	while (line[i])
	{
		if (!is_white_space(line[i]))
		{
			c = line[i];
			if (c == '|')
			{
				if (++k > 1)
					return (0);
			}
			else if (k)
				k--;
		}
		i++;
	}
	if (c == '|')
		return (0);
	return (1);
}


int	empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_white_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_befor_pipe(char *s, t_execmd	*befor_pipe)
{
	
	if (empty(s) == 1)
		return (1);
	else if (befor_pipe->av[0] == 0)
		return (1);
	else if (pip_syntax(s, 0, 0, 0) == 0)
		return (1);
	else 
		return (0);
}

t_defcmd	*pip_parsing(t_env **env, char **line_s, char *line_e)
{
	t_defcmd	*tree_head;
	t_execmd	*befor_pipe;

	tree_head = exe_parsing(env, line_s, line_e, 0);
	if (find("|", line_s, line_e))
	{
		tokenizer(line_s, line_e);
		befor_pipe = (t_execmd *)tree_head;
		if (check_befor_pipe(*line_s, befor_pipe))
			parsing_err(1);
		tree_head = construct_pipe(tree_head, pip_parsing(env, line_s, line_e));
	}
	return (tree_head);
}