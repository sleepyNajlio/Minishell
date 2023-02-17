#include "../minishell.h"

char	**list_to_table(t_env *env)
{
	int		n;
	int		i;
	char	**tab;

	n = ft_lstsize(env);
	i = 0;
	tab = malloc(sizeof(char *) * (n +1));
	while (env)
	{
		if (env->value)
		{
			tab[i] = join_free_s1(ft_strjoin(env->name, "="), env->value);
			i++;
		}
		env = env->next;
	}
	tab[i] = 0;
	return (tab);
}
