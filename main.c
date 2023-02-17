/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/10/17 07:18:19 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var;


void	handler(int sig)
{
	// sig = 0;
	(void)sig;
	g_var = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

char	*ft_read(t_env **env_list)
{
	char	*line;

	line = readline("$> ");
	if (!line)
	{
		free_env(env_list);
		write(1, "exit\n", 5);
		exit (g_var);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

void	ft_child(char *line, t_env **env)
{
	int		pid;
	int		exits;
	int		flag_in;
	int		flag_out;
	t_defcmd	*tree;

	flag_in = 0;
	flag_out = 0;
	pid = forkk();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		tree = line_parsing(env, line);
		free(line);
		executor(tree, &flag_out, &flag_in, env);
	}
	signal(SIGINT, SIG_IGN);
	wait(&exits);
	if ((WTERMSIG(exits) == 3 || WTERMSIG(exits) == 2) && g_var != -1)
		g_var = 128 + WTERMSIG(exits);
	else
	g_var = WEXITSTATUS(exits);
}

int	main(int argc, char **argv, char **env)
{
	static char	*line;
	t_env	*env_list;

	argv[argc] = 0;
	env_list = init_env(env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler);
		line = ft_read(&env_list);
		if (empty(line) == 1 || parent_builtin(line, &env_list))
		{
			free(line);
			continue ;
		}
		ft_child(line, &env_list);
		free(line);
	}
	return (0);
}
