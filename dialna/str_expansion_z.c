
#include "../minishell.h"

void	exit_exp(char **arg, int *i)
{
	char	*number;
	char	*new_arg;

	if (exit_stat == 23)
		exit_stat = 258;
	number = ft_itoa(exit_stat);
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

void	env_exp(char **arg, int *i, t_env *env)
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

void	expansion(char **str, int *i, t_env *env)
{
	if ((*str)[*i + 1] == '?')
		exit_exp(str, i);
	else
		env_exp(str, i, env);
}

char	*str_expansion(char *str, t_env *env)
{
	int	i;
	int	is_quote;

	i = 0;
	is_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (is_quote == 0)
				is_quote = str[i];
			else if (str[i] == is_quote)
					is_quote = 0;
		}
		if (str[i] == '$' && is_quote != '\'')
			expansion(&str, &i, env);
		else
			i++;
	}
	return (str);
}
