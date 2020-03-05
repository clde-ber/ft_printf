#include "ft_printf.h"

static unsigned int	len_int_u(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static unsigned int	ft_pow_u(unsigned int nb, unsigned int pow)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 1;
	while (i < pow)
	{
		res = res * nb;
		i++;
	}
	return (res);
}

const char		*ft_itoa_u(unsigned int n)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		k;
	char	*str;

	i = 0;
	k = n;
	j = len_int_u(k);
	if (!(str = malloc(sizeof(char) * (len_int_u(n) + 1))))
		return (0);
	while (j-- > 0)
		if (i < len_int_u(k))
		{
			str[j] = ((n / ft_pow_u(10, i)) % 10) + '0';
			i++;
		}
	str[len_int_u(k)] = '\0';
	return ((const char *)str);
}
