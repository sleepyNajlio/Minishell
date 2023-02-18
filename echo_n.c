#include "minishell.h"

int	ch_echo(char *s)
{
	if (ft_strlen(s) != 4)
		return (0);
	if (ft_tolower(s[0]) == 'e' && ft_tolower(s[1]) == 'c'
		&& ft_tolower(s[2]) == 'h' && ft_tolower(s[3]) == 'o')
		return (1);
	return (0);
	// if (ft_strcmp(s, "echo"))
	// 	return (1);
	// if (ft_strcmp(s, "ECHO"))
	// 	return (1);
	// return (0);
}

int	echo_options(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	my_echo(t_execmd *exec)
{
	int	i;
	int	no_arg;

	i = 1;
	no_arg = 0;
	if (exec->av[i])
	{
		while (echo_options(exec->av[i]))
		{
			no_arg = 1;
			i++;
		}
		while (exec->av[i])
		{
			printf("%s", exec->av[i]);
			i++;
			if (exec->av[i])
				printf(" ");
		}
	}
	if (no_arg == 0)
		printf("\n");
	exit(0);
}