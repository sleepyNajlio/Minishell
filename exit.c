/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 04:06:55 by hkhalil           #+#    #+#             */
/*   Updated: 2023/02/18 15:51:11 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *s)
{
	write(2, "exit: ", 7);
	write(2, s, ft_strlen(s));
	write(2, ": numeric argument required\n", 29);
	exit(255);
}

void	ft_exit(t_execmd *node)
{
	int	i;
	int	k;

	k = 0;
	while (node->av[k])
		k++;
	printf("hnaa2 \n");
	if (node->av[1])
	{
		i = 0;
		if (node->av[1][0] == '-')
			i++;
		while (node->av[1][i])
			if (!ft_isdigit(node->av[1][i++]))
				exit_error(node->av[1]);
		if (k > 2)
		{
			write(2, "exit: too many arguments\n", 26);
			exit_stat = 1;
			return ;
		}
		exit(ft_atoi(node->av[1]));
	}
	exit(exit_stat);
}
