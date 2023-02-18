#include "minishell.h"

void	panic_2(char *name)
{
	// printf("khra\n");
	if (errno == 22)
	{
		write(2, name, ft_strlen(name));
		write(2, ": is a directory\n", 18);
		exit(126);
	}
	perror(name);
	exit(126);
}


void	panic_4(char *name)
{
	if (ft_strchr(name, '/'))
		perror(name);
	else
	{
		write(2, name, ft_strlen(name));
		write(2, ": command not found\n", 21);
	}
	// printf("hna\n");
	// if (errno == 2)
	// 	exit(127);
	// else if (errno == 13)
	// 	exit(126);
	exit(127);
}

void	panic(char *name, int flag)
{
	//printf("%d\n", errno);
	if (flag == 4 && errno != 2)
		panic_2(name);
	if (errno == 2 || errno == 13)
		panic_4(name);
}