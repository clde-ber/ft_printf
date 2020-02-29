#include "ft_printf.h"

void		init_struct(t_flag *help)
{
	help->width = 0;
	help->precision = 0;
	help->set_prec = 0;
	help->rev = 0;
	help->zero = 0;
	help->ret = 0;
}

void		init_all_except_ret(t_flag *help)
{
	help->width = 0;
	help->precision = 0;
	help->set_prec = 0;
	help->rev = 0;
	help->zero = 0;
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

int		find_percent(const char *str)
{
	int i;

	i = 0;
	while (str[i] == '%')
		i++;
//	printf("i = %d\n", i);
	return (i);
}

int is_flag(const char c)
{
	if (c == '.' || c == '-' || c == '*' || ft_isdigit(c))
		return (1);
	return (0);
}

int is_conv(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

int find_index(int i, const char *str)
{
	while (str[i])
	{
		//printf("I (in find index) = %d\n", i);
		if (is_flag(str[i]) == 0 && is_conv(str[i]) == 0)
			return (i);
		i++;
	}
	if (str[i] == '\0')
		return (-1);
	return (0);
}

void fill_struct(t_flag *help, const char *format, va_list args)
{
	int j;

	j = 0;
	j++;
//	printf("&format[j] rev %c\n", format[j]);
	while (format[j] && (is_flag(format[j]) || is_conv(format[j])))
	{
//		printf("j = %d\n", j);
		while (format[j] == '-' || format[j] == '0')
		{
			if (format[j] == '-')
				help->rev = 1;
			if (format[j] == '0')
			{
				if (format[j + 1] == '-')
				{
					help->rev = 1;
				}
				else
				{
					help->zero = 1;
					help->rev = 0;
				}
			}
			j++;
		}
		if (format[j] == '*' || ft_isdigit(format[j]))
		{
			if (format[j] != '*')
			{
				help->width = ft_atoi(&format[j]);
		//		printf("help-w = %d\n", help->width);
				while (ft_isdigit(format[j]))
					j++;
			}
			else
			{
				if (!(help->width = va_arg(args, int)))
					help->width = 0;
				j++;
			}
			if (ft_isdigit(format[j]) || format[j] == '-')
			{
				if (ft_isdigit(format[j]) || format[j] == '-')
				{
					help->width = ft_atoi(&format[j]);
//					printf("&format[j] rev %s\n", &format[j]);
					while (ft_isdigit(format[j]) || format[j] == '-')
					j++;
				}
			}
		}
		if (format[j] == '.')
		{
			if (format[j + 1] == '*' || ft_isdigit(format[j + 1]))
			{
				help->set_prec = 1;
				j++;
				while (ft_isdigit(format[j]) || format[j] == '-')
				{
					help->precision = ft_atoi(&format[j]);
//					printf("&format[j] prec %s\n", &format[j]);
					while (ft_isdigit(format[j]) || format[j] == '-')
						j++;
				}
				if (format[j] == '*')
				{
					if (!(help->precision = va_arg(args, int)))
						help->precision = 0;
					j++;
				}
			}
			else
			{
				help->precision = 0;
				help->set_prec = 1;
				j++;
			}
		}
	//	printf("format[j]! %c\n", format[j]);
		if (is_conv(format[j]))
		{
			fill_struct_conv(help, format[j], args);
			init_all_except_ret(help);
		}
		j++;
		while (is_flag(format[j]))
		{
			help->ret++;
			write(1, &format[j], sizeof(char));
			j++;
		}
		}
//	printf("width %d\n", help->width);
//	printf("prec %d\n", help->precision);
//	printf("rev %d\n", help->rev);
//	printf("zero %d\n", help->zero);
//	printf("ret %d\n", help->ret);
}

void fill_struct_conv(t_flag *help, char c, va_list args)
{
	int type;
	int i;
	unsigned int x;
	unsigned long long l;
	void *res;

	type = 0;
	res = 0;
	x = 0;
	i = 0;
	l = 0;
	if (c == 's')
	{
		if (!(res = va_arg(args, char *)))
			help->ret += ft_putstr_len(c, "(null)", help);
		else
			help->ret += ft_putstr_len(c, res, help);
	}
	else if (c == 'd' || c == 'i' || c == 'c')
	{
		if (c != 'c')
		{
			type = va_arg(args, int);
			help->ret += ft_putstr_len(c, ft_itoa(type), help);
		}
		else
		{
			i = va_arg(args, int);
			help->ret += ft_putchar(i, help);
		}
	}
	else if (c == 'u')
	{
		type = va_arg(args, int);
		if (type > 0)
			help->ret += ft_putstr_len(c, ft_itoa(type), help);
		else
			help->ret += ft_putstr_len(c, ft_itoa_u(type), help);
	}
	else if (c == 'x' || c == 'X')
	{
		x = va_arg(args, unsigned int);
		if (x == 0)
		{
			help->ret += ft_putstr_len(c, "0", help);
		}
		else
			help->ret += ft_putstr_len(c, to_hex(c, x, "0123456789abcdef"), help);
	}
	else if (c == 'p')
	{
		if (!(l = (unsigned long long)va_arg(args, void *)))
			help->ret += ft_putstr_len(c, "0x0", help);
		else
			help->ret += ft_putstr_len(c, (char *)ft_strjoin("0x", to_hex(c, l, "0123456789abcdef")),
			help);
	}
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

char	*to_hex(char c, unsigned long long n, char *base)
{
	int i;
	char *str;
	unsigned long long k;

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
//	printf("to hex %s\n", str);
	return (str);
}

int ft_putchar(char c, t_flag *help)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (help->precision > 1 && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
	|| c == 'x' || c == 'X'))
		help->zero = 1;
	if (help->precision > 1 && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
	|| c == 'x' || c == 'x'))
		help->width = 0;
	if (help->precision < 0)
	{
		help->precision = -1;
		help->rev = 1;
		help->set_prec = 1;
	}
	if (help->width < 0)
	{
		help->width = -help->width;
		help->rev = 1;
	}
//	if (help->precision >= 0 && help->set_prec)
//		help->zero = 0;
	if (help->precision && help->width == 0 && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
	|| c == 'x' || c == 'x'))
		help->zero = 1;
//	if ((help->precision == 0 && help->set_prec == 1 && str[i] == '0' && str[i + 1] == 'x')
//		|| (str[i] == '0' && str[i + 1] == 'x'))
//		help->precision += 2;
	if (help->rev == 0)
	{
		while ((j < help->width - 1 && (help->set_prec == 0 || help->precision == -1))
		|| (j < help->width - help->precision && help->set_prec == 1))
		{
		//	if (help->zero == 1)
		//		write(1, "0", sizeof(char));
		//	else
				write(1, " ", sizeof(char));

			j++;
		}
		while (i < help->precision - 1)
		{
			if (help->zero == 1)
				write(1, "0", sizeof(char));
			else
				write(1, " ", sizeof(char));
			i++;
		}
		if (help->set_prec == 0 || (help->set_prec == 1 && help->precision != 0))
		{	write(1, &c, sizeof(char));
			help->ret++;}
	}
	else
	{
		if (help->set_prec == 0 || (help->set_prec == 1 && help->precision != 0))
		{	write(1, &c, sizeof(char));
			help->ret++;}
		while (i < help->precision - 1)
		{
		//	if (c == 'p')
		//		break ;
			if (help->zero == 1)
				write(1, "0", sizeof(char));
			else
				write(1, " ", sizeof(char));
			i++;
		}
		while (j + i < help->width - 1)
		{
			write(1, " ", sizeof(char));
			j++;
		}
	}
	return (j + i);
}

int ft_putstr(const char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(1, &str[i], sizeof(char));
			i++;
		}
	}
	return (i);
}

int ft_putstr_len(char c, const char *str, t_flag *help)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (help->precision > ft_strlen(str) && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
	|| c == 'x' || c == 'X'))
		help->zero = 1;
//	if ((help->precision > 1 && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
//	|| c == 'x' || c == 'x')))
//		help->width = 0;
	if (help->precision < 0)
	{
		help->precision = -1;
		help->set_prec = 1;
	}
	if (help->width < 0)
	{
		help->rev = 1;
		help->width = -help->width;
	}
//	if (help->precision >= 0 && help->set_prec)
//		help->zero = 0;
	if (help->precision && help->width > ft_strlen(str) && (c == 'i' || c == 'd'
	|| c == 'u' || c == 'p' || c == 'x' || c == 'x'))
		help->zero = 1;
//	if ((help->precision == 0 && help->set_prec == 1 && str[i] == '0' && str[i + 1] == 'x')
//		|| (str[i] == '0' && str[i + 1] == 'x'))
//		help->precision += 2;
//	if (help->width < help->precision)
//		help->width = 0;
	if (help->width <= ft_strlen(str) && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
	|| c == 'x' || c == 'X'))
		help->width = 0;
	if (c != 'c' && c != 's' && str[k] == '-')
		help->precision++;
//	if (help->precision < ft_strlen(str) && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
//	|| c == 'x' || c == 'X'))
//		help->precision = 0;
	if (help->rev == 0)
	{
		while ((((j < help->width - ft_strlen(str) && (help->precision == -1 ||
		help->set_prec == 0)) || (j < help->width - help->precision  &&
		help->set_prec == 1 && help->precision  != -1)) && (c == 's' || c == 'c'))
		|| (c != 's' && c != 'c' && ((j < help->width - ft_strlen(str) && (help->set_prec
		== 0 || (help->set_prec == 1 && (help->precision <= ft_strlen(str) && help->precision
		!= 0)) || (j < help->width - help->precision
		&& ((help->precision == 0 && help->set_prec == 1) || (help->precision >
		ft_strlen(str)))))))))
		{
		//	if (help->zero == 1)
		//		write(1, "0", sizeof(char));
		//	else
				write(1, " ", sizeof(char));

			j++;
		}
		if (str[i] == '-' && (help->set_prec == 0 || (help->set_prec == 1 && help->precision >= 1)))
		{
			write(1, "-", sizeof(char));
			k++;
		}
		while (i < help->precision - ft_strlen(str) && help->precision > ft_strlen(str))
		{
		//	if (c == 'p')
		//		break ;
			if (str[k] == '0' && str[k + 1] == 'x')
			{
				write(1, "0x", sizeof(char) * 2);
				k += 2;
			}
			if (help->zero == 1)
				write(1, "0", sizeof(char));
			else
				write(1, " ", sizeof(char));
			i++;
		}
		while ((str[k] && k < help->precision && help->set_prec &&
		help->precision != -1) || (str[k] && (help->set_prec == 0 ||
		(help->set_prec == 1 && help->precision == -1))) || (str[k] && (c == 'p'
		|| c == 'i' || c == 'd' || c == 'x' || c == 'X' || c == 'u') && ((((str[k] != '0'
		&& ft_strlen(str) == 1) || ft_strlen(str) > 1) || (str[k] == '0' && ft_strlen(str)
		== 1 && (help->set_prec == 0 || (help->set_prec == 1 && help->precision != 0)))))))
		{
			write(1, &str[k], sizeof(char));
			k++;
		}
	}
	else
	{
		if (str[i] == '-' && (help->set_prec == 0 || (help->set_prec == 1 && help->precision >= 1)))
		{
			write(1, "-", sizeof(char));
			k++;
		}
		while (((str[k] && k < help->precision && help->set_prec &&
		help->precision != -1) || (str[k] && (help->set_prec == 0 ||
		(help->set_prec == 1 && help->precision == -1)))) && (c == 's' || c == 'c'))
		{
			write(1, &str[k], sizeof(char));
			k++;
		}
		while (i < help->precision - ft_strlen(str) && help->precision > ft_strlen(str))
		{
		//	if (c == 'p')
		//		break ;
			if (help->zero == 1)
				write(1, "0", sizeof(char));
			else
				write(1, " ", sizeof(char));
			i++;
		}
		while (str[k] && (c == 'p'
		|| c == 'i' || c == 'd' || c == 'x' || c == 'X' || c == 'u') && ((((str[k] != '0'
		&& ft_strlen(str) == 1) || ft_strlen(str) > 1) || (str[k] == '0' && ft_strlen(str)
		== 1 && (help->set_prec == 0 || (help->set_prec == 1 && help->precision != 0))))))
		{
			write(1, &str[k], sizeof(char));
			k++;
		}
		while (j + k + i < help->width)
		{
			write(1, " ", sizeof(char));
			j++;
		}
	}
	return (j + k + i);
}
