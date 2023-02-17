#include "../minishell.h"

void	env_free(t_env **env)
{
	while (env && *env)
	{
		free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		*env = (*env)->next;
	}
}

void	pipe_free(t_pipecmd *tree)
{
	free(tree);
}

void	redir_free(t_redcmd *tree)
{
	free(tree->file);
	free(tree);
}

void	exec_free(t_execmd *tree)
{
	int	i;

	i = 0;
	while (tree->av[i])
	{
		free(tree->av[i]);
		i++;
	}
	free(tree);
}

void	master_free(t_defcmd *tree)
{
	t_execmd	*tree_e;
	t_redcmd	*tree_r;
	t_pipecmd	*tree_p;

	if (tree->type == PIPE)
	{
		tree_p = (t_pipecmd *)tree;
		master_free(tree_p->left);
		master_free(tree_p->right);
		pipe_free(tree_p);
	}
	else if (tree->type == REDIR)
	{
		tree_r = (t_redcmd *)tree;
		master_free(tree_r->cmd);
		redir_free(tree_r);
	}
	else
	{
		tree_e = (t_execmd *)tree;
		exec_free(tree_e);
	}
}