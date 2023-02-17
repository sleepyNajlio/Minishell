#include "minishell.h"

t_defcmd	*construct_pipe(t_defcmd *left, t_defcmd *right)
{
	t_pipecmd	*pipecmd;

	pipecmd = malloc(sizeof(*pipecmd));
	pipecmd->type = PIPE;
	pipecmd->left = left;
	pipecmd->right = right;
	return ((t_defcmd *)pipecmd);
}

t_defcmd	*construct_exe(void)
{
	t_execmd	*execmd;

	execmd = malloc(sizeof(*execmd));
	execmd->type = EXEC;
	return ((t_defcmd *)execmd);
}


t_defcmd	*construct_red(t_defcmd *cmd_child, char *file_name, int mode, int type)
{
	t_redcmd	*redcmd;

	redcmd = malloc(sizeof(*redcmd));
	redcmd->type = REDIR;
	redcmd->cmd = cmd_child;
	redcmd->file = file_name;
	redcmd->mode = mode;
	if (type == '<' || type == '*')
		redcmd->fd = 0;
	else
		redcmd->fd = 1;
	return ((t_defcmd *)redcmd);
}