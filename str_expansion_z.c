
#include "minishell.h"

void	expand_exit_code(char **arg, int *i)
{
	char	*number;
	char	*new_arg;

	if (g_var == 23)
		g_var = 258;
	number = ft_itoa(g_var);
	new_arg = join_free_s1(join_free_s1(ft_substr(*arg, 0, *i),
				number), &(*arg)[*i + 2]);
	free(number);
	free(*arg);
	*arg = ft_strdup(new_arg);
	free(new_arg);
	(*i)++;
}

void	found_env(char **arg, int *i, t_env *env, char *c)
{
	char	*v;
	char	*new_arg;

	v = ft_strdup(my_getenv(c, env));
	new_arg = join_free_s1(join_free_s1(ft_substr(*arg, 0, *i), v),
			&(*arg)[*i + ft_strlen(c) + 1]);
	free(*arg);
	*arg = ft_strdup(new_arg);
	free(new_arg);
	*i = *i + ft_strlen(v);
	free(v);
}

void	expand_env(char **arg, int *i, t_env *env)
{
	char	*new_arg;
	char	*c;

	c = ft_env_name(&(*arg)[*i + 1]);
	if (my_getenv(c, env))
		found_env(arg, i, env, c);
	else if (c[0])
	{
		new_arg = join_free_s1(ft_substr(*arg, 0, *i),
				&(*arg)[*i + ft_strlen(c) + 1]);
		free(*arg);
		*arg = ft_strdup(new_arg);
		free(new_arg);
	}
	else if ((*arg)[*i + 1] && ((*arg)[*i + 1] == '\''
				|| (*arg)[*i + 1] == '\"'))
	{
		new_arg = join_free_s1(ft_substr(*arg, 0, *i), &(*arg)[*i + 1]);
		free(*arg);
		*arg = ft_strdup(new_arg);
		free(new_arg);
	}
	else
		(*i)++;
	free(c);
}

void	expand(char **arg, int *i, t_env *env)
{
	if ((*arg)[*i + 1] == '?')
		expand_exit_code(arg, i);
	else
		expand_env(arg, i, env);
}

char	*str_expansion(char *str, t_env *env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else
				if (str[i] == quote)
					quote = 0;
		}
		if (quote != '\'' && str[i] == '$')
			expand(&str, &i, env);
		else
			i++;
	}
	return (str);
}
