#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *end_line(char *line)
{
    char *ret;

    ret = line + ft_strlen(line);
    return (ret);
}


t_defcmd	*line_parsing(t_env **env, char *line)
{
	t_defcmd	*tree_head;
	char	*end_s;

	end_s = end_line(line);
	tree_head = pip_parsing(env, &line, end_s);
	// find("", &line, end_s);
	// if (line != end_s)
	// 	exit(1);
	return (tree_head);
}