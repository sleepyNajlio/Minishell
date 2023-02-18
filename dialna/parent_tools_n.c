#include "../minishell.h"

void	panic_1(char *name, int flag)
{
	write(2, name, ft_strlen(name));
	if (flag)
		write(2, ": Permission denied\n", 21);
	else
		write(2, ": No such file or directory\n", 29);
	exit_stat = 1;
}

void	files_check(t_defcmd *redir, int *err_flag)
{
	t_redcmd	*tmp;
	int			fd;

	tmp = (t_redcmd *)redir;
	fd = open(tmp->file, tmp->mode);
	if (fd < 0)
	{
		close(fd);
		if (access(tmp->file, F_OK) == 0)
			panic_1(tmp->file, 1);
		else
			panic_1(tmp->file, 0);
		*err_flag = 1;
	}
	close(fd);
}

void	check_redir(t_defcmd *tree, int *err_flag)
{
	t_redcmd	*tree_r;

	if (tree->type == REDIR)
	{
		tree_r = (t_redcmd *)tree;
		check_redir(tree_r->cmd, err_flag);
		if (tree_r->fd == 0)
			files_check(tree, err_flag);
	}
}

void	open_files(t_defcmd *tree, t_env **my_env)
{
	t_redcmd	*tree_r;
	int			fd;

	tree_r = (t_redcmd *)tree;
	fd = open(tree_r->file, tree_r->mode, 0666);
	if (fd < 0)
		return ;
	close(fd);
	if (tree_r->cmd->type == REDIR)
		open_files(tree_r->cmd, my_env);
}


void	p_builtin_exec(t_defcmd *tree, int *done, t_env **env)
{
	t_defcmd	*tree_t;

	tree_t = tree;
	if (tree->type != PIPE)
	{
		check_redir(tree_t, done);
		if (*done == 0)
		{
			tree_t = tree;
			if (tree->type == REDIR)
				open_files(tree_t, env);
			tree_t = tree;
			while (tree_t->type != EXEC)
				tree_t = ((t_redcmd *)tree_t)->cmd;
			exit_parent(tree_t, done);
			if (*done == 0)
				cd_parent(tree_t, done, env);
			if (*done == 0)
				unset_parent(tree_t, done, env);
			if (*done == 0)
				export_parent(tree_t, done, env);
			// if (*done == 0)
			// 	pwd_parent(tree_t, done);
		}
	}
}