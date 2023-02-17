
#include "../minishell.h"

void	ch_wait(int pid)
{
	int exit;
	
	waitpid(pid, &exit, 0);
	if ((WTERMSIG(exit) == 2 || WTERMSIG(exit) == 3) && exit_stat != -1)
		exit_stat = WTERMSIG(exit) + 128;
	else
		exit_stat = WEXITSTATUS(exit);
}

void	sighandler(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	else if (sig == SIGINT)
		write(1,"\n", 1);
}

void	mini_child(char *line, t_env **env)
{
	t_defcmd	*tree;
	int			pid;
	int			in;
	int			out;

	out = 0;
	in = 0;
	pid = my_fork();
	if (pid == 0)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		tree = line_parsing(env, line);
		free(line);
		executor(tree, &out, &in, env);
	}
	signal(SIGINT, SIG_IGN);
	ch_wait(pid);
}

