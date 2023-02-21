/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 00:45:12 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 05:36:53 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_stat;

void	ctrls(int s)
{
	(void)s;
	g_stat = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	c_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrls);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*read_line(t_env **env)
{
	char	*buff;

	(void)env;
	buff = readline("TheShell-1.0$ ");
	if (!buff)
	{
		write(1, "exit\n", 5);
		exit (g_stat);
	}
	return (buff);
}

int	main(int ac, char **av, char **env)
{
	t_env		*my_env;
	static char	*line;

	(void) ac;
	(void) av;
	my_env = env_init(env);
	while (1)
	{
		c_signal();
		line = read_line(&my_env);
		if (line && *line && !empty(line))
			add_history(line);
		if (empty(line) == 1 || !mini_parent(line, &my_env))
		{
			free(line);
			continue ;
		}
		mini_child(line, &my_env);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	return (0);
}
