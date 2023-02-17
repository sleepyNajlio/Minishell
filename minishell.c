#include "minishell.h"

int	exit_stat;

void	ctrls(int s)
{
	(void)s;
	exit_stat = 1;
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

char	*read_line(t_env **env)
{
	char	*buff;

	buff = readline("TheShell-1.0$ ");
	if (!buff)
	{
		env_free(env);
		write(1, "exit\n", 5);
		exit (exit_stat);
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
			continue;
		}
		mini_child(line, &my_env);
		free(line);
  }
  return (0);
}