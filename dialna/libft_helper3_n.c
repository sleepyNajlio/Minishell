#include "../minishell.h"

int	word_count(char *str, char c)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] != c && str[i])
		{
			j = 1;
			i++;
		}
		if (j == 1)
			n++;
		if (str[i])
			i++;
	}
	return (n);
}

char	*freealloc(char **res, int w, int j)
{
	res[w] = malloc(sizeof(char) * j + 1);
	if (!res[w])
	{
		while (w > 0)
		{
			free(res[w - 1]);
			w--;
		}
		free(res);
		res = NULL;
		return (0);
	}
	return (res[w]);
}

void	*ft_memmove(void *dst, void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst > src)
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}

void	splitter(char **res, const char *s, char c, int n)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	w = 0;
	while (n > 0)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		if (!freealloc(res, w, j))
			return ;
		if (ft_memmove(res[w], &((void *)s)[i], j))
		{
			res[w][j] = '\0';
			w++;
			n--;
			i = i + j;
		}
	}
	res[w] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**res;
	int		j;
	int		n;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	n = word_count((char *)s, c);
	res = malloc(sizeof(char *) * (n + 1));
	if (!res)
		return (NULL);
	splitter(res, s, c, n);
	return (res);
}
