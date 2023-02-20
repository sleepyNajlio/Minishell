/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:23:36 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/20 20:23:48 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ch_pwd(char *s)
{
	if (ft_strlen(s) != 3)
		return (0);
	if (ft_tolower(s[0]) == 'p' && ft_tolower(s[1]) == 'w'
		&& ft_tolower(s[2]) == 'd')
		return (1);
	return (0);
}

void	my_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
		printf("%s\n", cwd);
	else
		perror("");
	exit(0);
}
