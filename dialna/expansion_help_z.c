#include "../minishell.h"

char	*ft_env_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != '$' && !is_white_space(s[i])
			&& s[i] != '\'' && s[i] != '\"')
		&& (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_'))
		i++;
	return (ft_substr(s, 0, i));
}

char	*my_getenv(char *s, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, s))
			return (env->value);
		env = env->next;
	}
	return (0);
}

char	*file_expansion(char *arg)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1]
			&& (arg[i + 1] == '\'' || arg[i + 1] == '\"'))
		{
			new_arg = join_free_s1(ft_substr(arg, 0, i), &arg[i + 1]);
			free(arg);
			arg = ft_strdup(new_arg);
			free(new_arg);
		}
		i++;
	}
	return (arg);
}