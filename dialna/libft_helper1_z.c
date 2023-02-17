#include "../minishell.h"

static int	nb_digit(unsigned int n)
{
	int	digit;

	digit = 0;
	while (n)
	{
		n = n / 10;
		digit++;
	}
	return (digit);
}

static	char	*alloc(int digit, int sign, unsigned int nb)
{
	char	*ret;

	ret = malloc(digit + 1);
	if (!ret)
		return (0);
	ret[digit] = '\0';
	if (sign == -1)
		ret[0] = '-';
	while (nb)
	{
		ret[digit - 1] = nb % 10 + '0';
		nb = nb / 10;
		digit--;
	}
	return (ret);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ret;
	char	*ret_ini;

	len = ft_strlen(s);
	ret = (char *) malloc(len + 1);
	if (!ret)
		return (0);
	ret_ini = ret;
	while (*s)
		*ret++ = *s++;
	*ret = 0;
	return (ret_ini);
}

char	*ft_itoa(int n)
{
	int				sign;
	int				digit;
	char			*ret;
	unsigned int	nb;

	sign = 1;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		nb = n * (-1);
		sign = -1;
	}
	else
		nb = n;
	digit = nb_digit(nb);
	if (sign == -1)
		digit += 1;
	ret = alloc(digit, sign, nb);
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		start = s_len;
	if (start + len > s_len)
		len = s_len - start;
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	ft_memcpy(ret, s + start, len);
	*(ret + len) = 0;
	return (ret);
}