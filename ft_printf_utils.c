#include "ft_printf.h"

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

const char	*join_a_free(const char *s1, const char *s2)
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
	free((char *)s1);
	return ((const char *)ptr);
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

//	printf("n = %u\n", n);
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
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (n > 0)
	{
		str[i] = base[n % ft_strlen(base)];
		n = n / ft_strlen(base);
		i++;
	}
	str[i] = '\0';
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
	return (newstr);
}

int check_conv(size_t i, const char *format)
{
	while (format[i] == '.' || format[i] == '*' || format[i] == '-' || ft_isdigit(format[i])
	|| format[i] == 'c' || format[i] == 's' || format[i] == 'p' || format[i] == 'i' || format[i]
	== 'd' || format[i] == 'x'|| format[i] == 'X' || format[i] == 'u')
		i--;
	if ((i == 0 && format[i] == '%') || (i > 0 && format[i] == '%' && format[i - 1] != '%'))
//	{
	//	printf("AAAAAAA");
		return (1);
//	}
	return (0);
}

const char	*extract_arg(size_t i, va_list args, const char *format)
{
		int type;

		type = 0;
	//	printf("i = %zu\n", i);
	while (ft_isdigit(format[i]) && check_conv(i, format))
//	{printf("format[i]%c\n", format[i]);
	i++;
	if (format[i] == 's' && check_conv(i, format))
		return (va_arg(args, char *));
	if ((format[i] == 'd' || format[i] == 'i'
		|| format[i] == 'c') && check_conv(i, format))
		return (format[i] != 'c') ?
		ft_itoa(va_arg(args, int))
		: char_to_s((unsigned char)va_arg(args, int));
	if (format[i] == 'u' && check_conv(i, format))
		return ((type = va_arg(args, int)) > 0) ? ft_itoa(type) : ft_itoa_u(type);
	if ((format[i] == 'x' || format[i] == 'X') && check_conv(i, format))
		return (to_hex(format[i], va_arg(args, unsigned int),
		"0123456789abcdef"));
	if (format[i] == 'p' && check_conv(i, format))
		return (ft_strjoin("0x", to_hex(format[i],
		va_arg(args, unsigned int), "0123456789abcdef")));
	if (check_conv(i, format) && format[i] == '.' && (ft_isdigit(format[i + 1]) ||
		format[i + 1] == '*'))
		return ((const char *)ft_precision(i, format, args));
	if ((format[i] == '*' || (format[i] == '%' && format[i + 1] != '%'))
		&& check_conv(i, format))
		return ((const char *)ft_spacing(i, format, args));
	if (format[i] == '0' && check_conv(i, format))
		return (ft_strjoin("f0", ""));
	if (format[i] == '-' && check_conv(i, format))
		return (ft_strjoin("f-", ""));
	return (ft_strjoin("@", char_to_s(format[i])));
}

char *ft_modify(int i, char **tab, char *flag)
{
	int j;
	int value;

	j = 0;
	value = 0;
//	printf("i = %d\n", i);
//	printf("flag = %s\n", flag);
	while (flag[j++])
		if (ft_isdigit(flag[j]))
		{
	//		printf("j = %zd\n", j);
			value = ft_atoi(&flag[j]);
			break ;
		}
//	while (tab[i][0] == 'f' || tab[i][0] == '@')
//			i++;
//	printf("i = %d\n", i);
//	printf("value = %zu\n", value);
	if (flag[1] == '0')
		tab[i] = replace_spaces(tab[i]);
	if (flag[1] == '-')
		tab[i] = rev_flag(tab[i]);
	if (flag[1] == '.')
	{
		if (value < ft_strlen(tab[i]))
			tab[i][value - 1] = '\0';
		else
			tab[i] = (char *)join_a_free(replace_spaces(ft_spaces(value - ft_strlen(tab[i]),
			tab[i])), "");
	}
	if (flag[1] == '*')
	{
		if (value > ft_strlen(tab[i]))
			tab[i] = (char *)join_a_free(ft_spaces(value - ft_strlen(tab[i]) - 1, tab[i]), "");
	}
//	printf("tab[i] = %s\n", tab[i]);
	return (tab[i]);
}

char *ft_spacing(size_t i, const char *format, va_list args)
{
	const char *width;
	const char *ret;

	width = "0";
//	printf("FORMAT[I + 1] %c\n", format[i + 1]);
	if (ft_isdigit(format[i + 1]))
	{
		ret = ft_strjoin("f*", char_to_s(format[i + 1]));
		i++;
		while (ft_isdigit(format[i + 1]))
		{
			ret = ft_strjoin(ret, char_to_s(format[i + 1]));
			i++;
		}
		return ((char *)ret);
	}
	else if (format[i + 1] == '*')
	{
		if(!(width = ft_itoa(va_arg(args, int))))
			return (char_to_s('0'));
		return ((char *)ft_strjoin("f*", width));
	}
	else
		return ((char *)no_arg((char *)extract_arg(i + 2, args, format)));
}

char *ft_precision(size_t i, const char *format, va_list args)
{
	const char *nb_char;
	const char *ret;

	nb_char = "0";
	if (ft_isdigit(format[i + 1]))
	{
		ret = ft_strjoin("f.", char_to_s(format[i + 1]));
		i++;
		while (ft_isdigit(format[i + 1]))
		{
			ret = ft_strjoin(ret, char_to_s(format[i + 1]));
			i++;
		}
		return ((char *)ret);
	}
	else if (format[i + 1] == '*')
	{
		if(!(nb_char = ft_itoa(va_arg(args, int))))
			return (char_to_s('0'));
		return ((char *)ft_strjoin("f.", nb_char));
	}
	else
		return ((char *)no_arg((char *)extract_arg(i + 2, args, format)));
}

char *no_arg(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char *replace_spaces(char *str)
{
	size_t i;

	i = 0;
	while (str[i] == ' ')
	{
		str[i] = '0';
		i++;
	}
	return (str);
}

char *rev_flag(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	str = (char *)ft_strjoin(&str[i], "");
	while (j < i)
	{
		str = (char *)ft_strjoin(str, " ");
		j++;
	}
	return (str);
}

char *ft_spaces(size_t value, char *param)
{
	size_t i;
	char *str;

	i = 0;
	if (!(str = malloc(sizeof(char) * (value + 1))))
		return (0);
	while (i + ft_strlen(param) < value)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_is_value(char c)
{
	if (c == '%' || c == '*')
		return (1);
	return (0);
}

void ft_putchar(char c)
{
	write(1, &c, sizeof(char));
}

void ft_putstr(char *str)
{
	size_t i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			i++;
		}
	}
}
