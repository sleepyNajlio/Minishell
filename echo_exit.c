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

void	panic_exit(char *s)
{
	write(2, "exit: ", 7);
	write(2, s, ft_strlen(s));
	write(2, ": numeric argument required\n", 29);
	exit(255);
}

void	my_exit(t_execmd *exec)
{
	int	j;
	int	i;

	j = 0;
	while (exec->av[j])
		j++;
	printf("hnaa2 \n");
	if (exec->av[1])
	{
		i = 0;
		if (exec->av[1][0] == '-')
			i++;
		while (exec->av[1][i])
			if (!ft_isdigit(exec->av[1][i++]))
				panic_exit(exec->av[1]);
		if (j > 2)
		{
			write(2, "exit: too many arguments\n", 26);
			exit_stat = 1;
			return ;
		}
		exit(ft_atoi(exec->av[1]));
	}
	exit(exit_stat);
}