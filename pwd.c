/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 04:42:58 by hkhalil           #+#    #+#             */
/*   Updated: 2023/02/18 17:22:13 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ch_pwd(char *s)
{
	if (ft_strlen(s) != 3)
		return (0);
	if (ft_tolower(s[0]) == 'p' && ft_tolower(s[1]) == 'w'
		&& ft_tolower(s[2]) == 'd')
		return (1);
	return (0);
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024))
		printf("%s\n", cwd);
	exit(0);
}

