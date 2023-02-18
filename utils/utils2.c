#include "../minishell.h"

// int	ft_tolower(int c)
// {
// 	if (c >= 'A' && c <= 'Z')
// 		return (c + 32);
// 	return (c);
// }

int	valid_name(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
	{
		exit_stat = -6;
		return (0);
	}
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
		{
			exit_stat = -6;
			return (0);
		}
		i++;
	}
	return (1);
}
