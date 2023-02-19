
#include "minishell.h"

int	exist_check(t_env **env, char *s, int flag)
{
	char **v;

    v = ft_split(s, '=');
	while (env && *env)
	{
		if (!ft_strcmp((*env)->name, v[0]))
		{
			if (flag)
			{
                if ((*env)->value)
                    free(((*env)->value));
				if (v[1])
                {
					(*env)->value = ft_strdup(v[1]);

                }
				else
					(*env)->value = ft_strdup("");
				(*env)->sep = ft_strchar(s, '=');
			}
            free(v[0]);
            free(v[1]);
            free(v);
			return (1);
		}
		(*env) = (*env)->next;
	}
    free(v[0]);
	free(v[1]);
	free(v);
    v = NULL;
	return (0);
}

void	with_value(t_env **env, char *s, t_env *addr)
{
	char	**v;

	v = ft_split(s, '=');
	if (v && v[0] && !v[1])
	{
		free(v[1]);
		v[1] = ft_strdup("");
	}
	if (v && v[0] && exist_check(&addr, s, 1))
		;
	else
	{
		if (v && v[0] && name_check(v[0]))
			ft_lst_add_back(env,
				ft_lstnew(ft_strdup(v[0]), ft_strdup(v[1]), ft_strchar(s, '=')));
		else
		{
			exit_stat = -6;
			printf("export: `%s': not a valid identifier\n", s);
		}
	}
	free(v[0]);
	free(v[1]);
	free(v);
    v = NULL;
}

void	without_val(t_env **env, char *s, t_env	*addr)
{
	if (exist_check(&addr, s, 0))
		;
	else if (name_check(s))
	{
		ft_lst_add_back(env,
			ft_lstnew(ft_strdup(s), "\0", ft_strchar(s, '=')));
	}
	else
	{
		exit_stat = -6;
		printf("export: `%s': not a valid identifier\n", s);
	}
}

void	export_noargs(t_env **env)
{
	while ((*env))
	{
		if (!(*env)->sep)
			printf("declare -x %s\n", (*env)->name);
		else if (!(*env)->value)
			printf("declare -x %s%c\"\"\n", (*env)->name, (*env)->sep);
		else
			printf("declare -x %s%c\"%s\"\n",
				(*env)->name, (*env)->sep, (*env)->value);
		(*env) = (*env)->next;
	}
	exit_stat = 0;
}


void	my_export(t_execmd *cmd, t_env **env)
{
	int			i;
	t_env	*addr;

	i = 1;
	if (!cmd->av[i])
		export_noargs(env);
	while (cmd->av[i])
	{
		addr = *env;
		if (ft_strchr(cmd->av[i], '='))
			with_value(env, cmd->av[i], addr);
		else
			without_val(env, cmd->av[i], addr);
		i++;
	}
}