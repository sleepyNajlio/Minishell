
#include "../minishell.h"

int	forkk(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("fork failed !");
		exit(1);
	}
	return (pid);
}




