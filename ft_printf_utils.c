#include "ft_printf.h"

int		check_format(const char *format)
{
	const char *c;
	size_t i;

	i = 0;
	c = format;
	i = (c[i] == '%') ? ++i : 0;
	if (i == 0)
		return (0);
	while (c[i] == 'd' || c[i] == 'i' || c[i] == 'o' || c[i] == 'u' || c[i] == 'x' || c[i] == 'X'
		|| c[i] == 'c' || c[i] == 's' || c[i] == '*' || c[i] == '#' || c[i] == '0' || c[i] == '-'
		|| ft_isdigit(c[i]) || c[i] == '$')
	{
		i = (c[i] == '*' || c[i] == '#' || c[i] == '0' || c[i] == '-' || ft_isdigit(c[i])) ? ++i : i;
		i = (c[i] == 'd' || c[i] == 'i' || c[i] == 'o' || c[i] == 'u' || c[i] == 'x'
		|| c[i] == 'X' || c[i] == 'c' || c[i] == 's' || ft_isdigit(c[i])) ? ++i : i;
		i = (c[i] == '*') ? ++i : i;
		i = (ft_isdigit(c[i])) ? ++i : i;
		i = (c[i] == '$') ? ++i : i;
		i = (c[i] == 'd' || c[i] == 'i' || c[i] == 'o' || c[i] == 'u' || c[i] == 'x' || c[i] == 'X'
		|| c[i] == 'c' || c[i] == 's') ? ++i : i;
		i = (c[i] == '\n') ? ++i : i;
	}
	if (i == ft_strlen(c))
		return (i);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}

const char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (0);
	if (!(ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
//	free (s2);
//	free(s1);
	return ((const char *)ptr);
}

const char	*find_param(const char *format, const char *params)
{
	size_t find_arg;
	int i;

	find_arg = 1;
	i = -1;
	while (format[++i])
		if (ft_isdigit(format[i]))
		{
			find_arg = format[i] - 48;
			break ;
		}
	i = -1;
		while (params[++i + 1] && find_arg > 1)
			find_arg = (params[i] == ',' && params[i + 1] == ' ') ? --find_arg : find_arg;
		params = (const char *)ft_memmove(params, &params[i + 1], i);
		i = 0;
		while(params[i++])
			if (params[i] == '\0' || params[i] == ',')
			((char *)params)[i] = '\0';
		return (params[0] == '\0') ? 0 : params;
}

const void	*ft_memmove(const void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (src <= dst)
	{
		tmp_dst = (unsigned char *)dst;
		tmp_src = (unsigned char *)src;
		while (len--)
			tmp_dst[len] = tmp_src[len];
	}
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return ((const char *)dst);
}

void		*ft_convert(char *str, va_list args, char *format)
{
	printf("sizeof %zu\n", sizeof(args));
	args = (sizeof(args) == sizeof(char)) ? va_arg(args, char) : args;
	args = (sizeof(args) == sizeof(unsigned char)) ? va_arg(args, unsigned char) : args;
	args = (sizeof(args) == sizeof(char *)) ? va_arg(args, char *) : args;
	args = (sizeof(args) == sizeof(int)) ? va_arg(args, int) : args;
	args = (sizeof(args) == sizeof(unsigned int) && args < 0) ? va_arg(args, unsigned int) : args;
	args = (sizeof(args) == sizeof(long) && ft_strlen(args) == -1) ? va_arg(args, long) : args;
	args = (sizeof(args) == sizeof(unsigned long) && args < 0 && ft_strlen(args) == -1) ? va_arg(args, unsigned long) : args;
	printf("value %s\n", args);
	printf("strlen %d\n", ft_strlen(args));
	write(1, "a", 1);
	return (args);
}

static int	len_int(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	else if (n <= 2147483647 && n > -2147483648)
	{
		if (n == 0)
			return (1);
		if (n < 0)
		{
			n = -n;
			i += 1;
		}
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
	}
	return (i);
}

static int	ft_pow(int nb, int pow)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < pow)
	{
		res = res * nb;
		i++;
	}
	return (res);
}

const char		*ft_itoa(long n)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if (n == -2147483648)
		return ((const char *)ft_strjoin("-2147483648", ""));
	i = -1;
	k = n;
	j = len_int(k);
	if (!(str = malloc(sizeof(char) * (len_int(n) + 1))))
		return (0);
	n = (n < 0) ? -n : n;
	while (j-- > 0)
		if (i++ <= len_int(k))
			str[j] = ((n / ft_pow(10, i)) % 10) + '0';
	str[len_int(k)] = '\0';
	str[0] = (k < 0) ? '-' : str[0];
	return ((const char *)str);
}
