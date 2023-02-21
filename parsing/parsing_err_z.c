/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_err_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 23:52:56 by fel-fil           #+#    #+#             */
/*   Updated: 2023/02/21 00:07:35 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing_err(int id)
{
	if (id == 1)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		exit(23);
	}
	if (id == 2)
	{
		perror("syntax error");
		exit(1);
	}
	if (id == 3)
	{
		perror("missing file for redirection");
		exit(1);
	}
	if (id == 4)
	{
		perror("Too many args");
		exit(1);
	}
}
