#include "minishell.h"

void	wait_p(int pid)
{
	int	first;
	int	last;

	waitpid(pid, &last, 0);
	while (wait(&first) > 0)
	{
		if ((WTERMSIG(first) == 3 || WTERMSIG(first) == 2)
			&& (WTERMSIG(last) != 3 && WTERMSIG(last) != 2))
		exit_stat = -1;
	}
	exit(WEXITSTATUS(last));
}

void	my_pipe(int p[2])
{
	if (pipe(p) < 0)
		perror("pipe error");
}

void	exec_pipe(t_defcmd *tree, int *out, int *in, t_env **my_env)
{
	t_pipecmd	*tree_p;
	int		pipe[2];
	int		pid;

	tree_p = (t_pipecmd *)tree;
	my_pipe(pipe);
	pid = my_fork();
	if (pid == 0)
	{
		close(pipe[0]);
		dup2(pipe[1], 1);
		close(pipe[1]);
		execution_time(tree_p->left, out, in, my_env);
	}
	pid = my_fork();
	if (pid == 0)
	{
		close(pipe[1]);
		dup2(pipe[0], 0);
		close(pipe[0]);
		execution_time(tree_p->right, out, in, my_env);
	}
	close(pipe[0]);
	close(pipe[1]);
	wait_p(pid);
}
