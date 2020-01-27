#include "ft_printf.h"

int		ft_format(const char *format)
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
		|| ft_isdigit(c[i]) || c[i] == '$' || c[i] == '%')
	{
		i = (c[i] == '*' || c[i] == '#' || c[i] == '0' || c[i] == '-' || ft_isdigit(c[i])) ? ++i : i;
		i = (c[i] == 'd' || c[i] == 'i' || c[i] == 'o' || c[i] == 'u' || c[i] == 'x'
		|| c[i] == 'X' || c[i] == 'c' || c[i] == 's' || ft_isdigit(c[i])) ? ++i : i;
		i = (c[i] == '*' || c[i] == '%') ? ++i : i;
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
	return ((const char *)ptr);
}

char	**ft_order_params(size_t j, const char *params, const char *format)
{
	char **tmp;
	char **tmp_ordered;
	size_t i;
	size_t k;

	i = 0;
	k = -1;
	tmp = ft_split(params, ',');
	tmp_ordered = ft_split(params, ',');
	while (tmp[i])
	{
		printf("i = %zu\n", i);
		printf("tmp[i] %s\n", tmp[i]);
		i++;
	}
	i = -1;
	while (format[++i + 2])
		if (ft_isdigit(format[i + 1]) && format[i + 2] == '$' && ft_is_value(format[i]))
		{
			tmp_ordered[++k] = tmp[format[i + 1] - 48 - 1];
			printf("ordered tmp index %d\n", format[i + 1] - 48 - 1);
			printf("tmp[x] % s\n", tmp[format[i + 1] - 48 - 1]);
			printf("i = %zu!\n", i);
		}
	tmp_ordered[++k] = 0;
	k = 0;
	while (tmp_ordered[k])
	{
		printf("k = %zu\n", k);
		printf("tmp_ordered[k] %s\n", tmp_ordered[k]);
		k++;
	}
	return (tmp);
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

const char		*ft_itoa(int n)
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

int	ft_atoi(const char *str)
{
	int i;
	int j;
	int res;

	i = 0;
	j = 0;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			j = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (ft_isdigit(str[i]))
		res = res * 10 + (str[i++] - 48);
	if (res == -2147483648)
		return (res);
	if (j < 0)
		res = res * j;
	return (res);
}

size_t	ft_nb_params(const char *format)
{
	size_t i;
	size_t nb_params;

	nb_params = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' || format[i] == '*')
			nb_params++;
		i++;
	}
	return (nb_params);
}

char	ft_type(const char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'c' || str[i] == 's'
		|| str[i] == 'u' || str[i] == 'x'|| str[i] == 'X' || str[i] == 'p')
			break ;
	return (str[i]);
}

size_t	ft_index(const char *str, const char *format)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'c' || str[i] == 's'
		|| str[i] == 'u' || str[i] == 'x'|| str[i] == 'X' || str[i] == 'p')
			break ;
		i++;
	}
	printf("ft_index %zu\n", i + 1);
	return (i + 1);
}

char	*char_to_s(int x)
{
	char c;
	char *s;

	if (!(s = malloc(sizeof(char) * 2)))
		return (0);
	c = x;
	s[0] = c;
	s[1] = '\0';
	return (s);
}

char	*to_hex(char c, unsigned int n, char *base)
{
	int i;
	char *str;
	unsigned int k;

	k = n;
	i = 0;
	while (k > 0)
	{
		k = k / ft_strlen(base);
		i++;
	}
	if (!(str = malloc(sizeof(char) * 1024)))
		return (0);
	printf("i === %d\n", i);
	i = 0;
	while (n > 0)
	{
		str[i] = base[n % ft_strlen(base)];
		n = n / ft_strlen(base);
		i++;
	}
	str[ft_strlen(str)] = '\0';
	str = revstr(str);
	if (c == 'X')
		str = str_toupper(str);
	return (str);
}

char *str_toupper(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

char	*revstr(char *str)
{
	size_t i;
	size_t j;
	char *newstr;

	j = 0;
	i = ft_strlen(str) + 1;
	if (!(newstr = malloc(sizeof(char) * i)))
		return (0);
	while (i - 1 > 0)
	{
		newstr[j] = str[--i - 1];
		j++;
	}
	newstr[j] = '\0';
	printf("newstr %s\n", newstr);
	return (newstr);
}

const char	*extract_arg(size_t i, const char *str, va_list args, char *format)
{
	if (ft_type(&format[i]) == 's')
		return (ft_strjoin(str, va_arg(args, char *)));
	if (ft_type(&format[i]) == 'd' || ft_type(&format[i]) == 'i' ||
	ft_type(&format[i]) == 'c')
		return (ft_type(&format[i]) != 'c') ? ft_strjoin(str, ft_itoa(va_arg(args, int)))
		: ft_strjoin(str, char_to_s((unsigned char)va_arg(args, int)));
	if (ft_type(&format[i]) == 'u')
		return (ft_strjoin(str, ft_itoa(va_arg(args, unsigned int))));
	if (ft_type(&format[i]) == 'x' || ft_type(&format[i]) == 'X')
		return (to_hex(ft_type(&format[i]), va_arg(args, unsigned int), "0123456789abcdef"));
	if (ft_type(&format[i]) == 'p')
		return (ft_strjoin(str, ft_itoa(va_arg(args, unsigned int))));
		i += ft_index(&format[i], format);
		printf("%zu\n", i);
		printf("str %s\n", str);
	return (str);
}

int		ft_is_value(char c)
{
	if (c == '%' || c == '*')
		return (1);
	return (0);
}

char **ft_rewrite_format(const char *format)
{
	int i;
	int j;
	int nb_str;
	char **n_format;

	i = -1;
	j = 1;
	nb_str = 0;
	while (format[++i + 2])
		if (ft_is_value(format[i]) && ft_isdigit(format[i + 1]) && format[i + 2] == '$')
				nb_str++;
	printf("nb_str %d\n", nb_str);
	if (!(n_format = malloc(sizeof(char *) * (nb_str + 1))))
		return (0);
	i = -1;
	n_format[nb_str] = 0;
	while (format[++i + 2])
		if (ft_isdigit(format[i + 1]) && format[i + 2] == '$' && ft_is_value(format[i]))
		{	n_format[format[i + 1] - 48 - 1] = ft_strjoin(&format[i], "");
			printf("attention %s\n", n_format[format[i + 1] - 48 - 1]);
			printf("index %d\n", format[i + 1] - 48 - 1);
		}
	return (n_format);
}

char *ft_replace_format(char **new_format, const char *format, char *n_format)
{
	size_t i;
	size_t j;

	i = -1;
	j = 1;
	while (format[++i])
		if (ft_isdigit(format[i + 1]) && format[i + 2] == '$' && ft_is_value(format[i]))
		{
			i = -1;
			while (new_format[++i])
			{
				while (new_format[i][++j])
					if (ft_is_value(new_format[i][j]))
						new_format[i][j] = '\0';
				j = 0;
			}
			while(new_format[j])
			{
				n_format = (j == 0) ? ft_strjoin(new_format[j], "")
				: ft_strjoin(n_format, new_format[j]);
				j++;
			}
			printf("FORMAT %s\n", n_format);
			return (n_format);
		}
	printf("\na\n");
	return (format);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	if (!(ptr = (void *)malloc(count * size)))
		return (0);
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

static size_t	len_wd(char const *str, int c)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

static size_t	count_malloc(char const *s, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (s[i] == '\0' || c == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void		*ft_free(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!s || !*s)
		return ((char **)ft_calloc(2, sizeof(char *)));
	if (!(res = malloc(sizeof(char *) * (count_malloc(s, c) + 1))))
		return (0);
	while (i < ft_strlen(s))
	{
		while (j < count_malloc(s, c) && s[i] && s[i] != c)
		{
			if (!(res[j] = malloc(sizeof(char) * (len_wd(&s[i], c) + 1))))
				return (ft_free(res, j));
			res[j] = ft_memmove(res[j], &s[i], len_wd(&s[i], c) + 1);
			res[j][len_wd(&s[i], c)] = '\0';
			j++;
			i += len_wd(&s[i], c);
		}
		i++;
	}
	res[count_malloc(s, c)] = 0;
	return (res);
}
