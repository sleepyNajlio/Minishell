/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_z.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nloutfi <nloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 05:37:15 by nloutfi           #+#    #+#             */
/*   Updated: 2023/02/21 05:37:44 by nloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("err fork");
		exit(1);
	}
	return (pid);
}

void	hd_handler(int sig)
{
	sig = 1;
	write(1, "\n", 1);
	exit(sig);
}

void	heredoc_child(char *delimiter, char *path)
{
	int		fd;
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, hd_handler);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(path);
	line = readline("> ");
	while (line && ft_strcmp(line, delimiter))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(delimiter);
	close(fd);
	if (line)
		free(line);
	exit(0);
}

char	*open_heredoc(char *delimiter)
{
	int		id;
	char	*path;
	int		exits;

	path = ft_strjoin("/tmp/", delimiter);
	id = my_fork();
	if (id == 0)
		heredoc_child(delimiter, path);
	else
	{
		free(delimiter);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(id, &exits, 0);
		if (WEXITSTATUS(exits) == 1)
			exit(1);
	}
	return (path);
}
