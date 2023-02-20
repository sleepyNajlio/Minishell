/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:27:07 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/20 20:25:28 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	panic_2(char *name)
{
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
	exit(127);
}

void	panic(char *name, int flag)
{
	if (flag == 4 && errno != 2)
		panic_2(name);
	if (errno == 2 || errno == 13)
		panic_4(name);
}
