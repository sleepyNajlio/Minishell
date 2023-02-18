#include "minishell.h"

char	**env_tab(t_env *my_env)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(my_env);
	ret = malloc(sizeof(char *) * (size + 1));
	while (my_env)
	{
		if (my_env->value)
			ret[i++] = join_free_s1(ft_strjoin(my_env->name, "="), my_env->value);
		my_env = my_env->next;
	}
	ret[i] = 0;
	return (ret);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long long	n;	
	int					sign;
	int					i;

	sign = 1;
	i = -1;
	n = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(str[++i]))
		n = (n * 10) + (str[i] - '0');
	if (n > 9223372036854775807)
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (n * sign);
}