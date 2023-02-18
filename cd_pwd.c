#include "minishell.h"

int	ch_cd(t_execmd *tree_e, t_env **my_env)
{
	if (!ft_strcmp(tree_e->av[0], "cd"))
	{
		my_cd(tree_e, *my_env);
		if (errno == 13 || errno == 2)
			exit(1);
		exit(0);
	}
	return (0);
}
void	pwd_update(t_env **env, char *path)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp("PWD", tmp->name))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(path);
			free(path);
			return ;
		}
		tmp = tmp->next;
	}
	ft_lst_add_back(env, ft_lstnew(ft_strdup("PWD"), ft_strdup(path)));
	free(path);
}

void	my_cd(t_execmd *exec, t_env *env)
{
	if (exec->av[1])
	{
		if (chdir(exec->av[1]))
		{
			write(2, "cd: ", 5);
			perror(exec->av[1]);
			exit_stat = 1;
			return ;
		}
		pwd_update(&env, getcwd(NULL, 0));
	}
	if (!(exec->av[1]))
	{
		while (env)
		{
			if (!ft_strcmp(env->name, "HOME"))
				chdir(env->value);
			env = env->next;
		}
		exit_stat = 0;
	}
}

int	ch_pwd(char *s)
{
	// if (ft_strlen(s) != 3)
	// 	return (0);
	// if (ft_tolower(s[0]) == 'p' && ft_tolower(s[1]) == 'w'
	// 	&& ft_tolower(s[2]) == 'd')
	// 	return (1);
	// return (0);
	printf("hna\n");
	if (ft_strcmp(s, "pwd") == 0)
		return (1);
	if (ft_strcmp(s, "PWD") == 0)
		return (1);
	return (0);
}

void	my_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
		printf("%s\n", cwd);
	exit(0);
}