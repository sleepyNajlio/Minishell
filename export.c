
#include "minishell.h"

int	if_exist_add(t_env **env, char *s, int flag)
{
	char **v = ft_split(s, '=');
	while (env && *env)
	{
		if (!ft_strcmp((*env)->name, v[0]))
		{
			if (flag)
			{
				if (v[1])
					(*env)->value = ft_strdup(v[1]);
				else
					(*env)->value = ft_strdup("");
				(*env)->sep = ft_strchar(s, '=');
			}
			return (1);
		}
		(*env) = (*env)->next;
	}
	return (0);
}

void	global_env(t_env **env, char *s, t_env *addr)
{
	char	**v;

	v = ft_split(s, '=');
	if (v && v[0] && !v[1])
	{
		free(v[1]);
		v[1] = ft_strdup("");
	}
	if (v && v[0] && if_exist_add(&addr, s, 1))
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
}

void	local_env(t_env **env, char *s, t_env	*addr)
{
	if (if_exist_add(&addr, s, 0))
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

void	ft_export(t_execmd *cmd, t_env **env)
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
			global_env(env, cmd->av[i], addr);
		else
			local_env(env, cmd->av[i], addr);
		
		i++;
	}
}
