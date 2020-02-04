#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	const char **tab;
	size_t i;
	size_t j;
	int nb_args;
	va_list	args;
	int ret;

	j = -1;
	i = 0;
	nb_args = 0;
	ret = 0;
	va_start(args, format);
	while (format[++j])
	{
		if (format[j] == '%' && (ft_isdigit(format[j + 1]) || format[j + 1] == '*'))
		{
			nb_args++;
			if (nb_args == 1)
				i = j;
		}
		if (nb_args == 0)
		{
			if (format[j] == '%' && format[j + 1] == '%')
				while (format[j + 1] == '%')
				{
					ft_putchar(format[j + 1]);
					j++;
				}
			else
				ft_putchar(format[j]);
			ret++;
		}
	}
	tab = ft_fill_str(nb_args, &format[i], args);
	i = 0;
	while (i < nb_args)
	{
		ft_putstr(tab[i]);
		ret += ft_strlen(tab[i]);
		i++;
	}
	j = -1;
	printf("nb_args %zu\n", nb_args);
	while (format[++j] && nb_args)
		if (format[j] == '%' && format[j + 1] == '%')
			while (format[j] == '%')
				j++;
		else if (format[j] == '%')
			nb_args--;
	printf("j === %zu\n", j);
		while (format[j] == '.' || format[j] == '*' || format[j] == '0'
		|| format[j] == '-' || format[j] == 'd' || format[j] == 'i' ||
		format[j] == 'c' || format[j] == 's' || format[j] == 'u' ||
		format[j] == 'x'|| format[j] == 'X' || format[j] == 'p' ||
		ft_isdigit(format[j]))
			j++;
	ft_putstr(&format[j]);
	ret += ft_strlen(&format[j]);
	va_end(args);
	return (ret);
}

/*#include "ft_printf.h"
int	ft_printf(const char *format, ...)
{
	int i;
	int j;
	const char **stock;
	const char *output;
	int	*fct_ptr;
	i = -1;
	j = -1;
	while (format[++i])
	{
		if (check_format(format))
			if (find_conv_o_flag(format[i]))
			{
				fct_ptr = find_conv_o_flag(format[i]);
				stock[j] = find_param(format, str);
				stock[j] = app_fct(stock[j], &fct_ptr);
				j++;
			}
		else
			return 0;
	}
	stock[j] = 0;
	while (stock[j])
		output = (j == 0) ? ft_strjoin(stock[j], "") : ft_strjoin(output, stock[j]);
	return (ft_strlen(output));
	printf("%d\n", check_format(format));
	printf("%s\n", params);
	ft_transform_printf(format, ...);
	printf("%s\n", find_param(format, params));
}*/
➜  printf cat ft_printf_utils.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 14:46:53 by clde-ber          #+#    #+#             */
/*   Updated: 2020/02/04 14:06:37 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*int		ft_format(const char *format)
{
	const char *c;
	size_t i;
	i = 0;
	c = format;
	i = (c[i] == '%') ? ++i : 0;
	if (i == 0)
		return (0);
	while (c[i] == 'd' || c[i] == 'i' || c[i] == 'o' || c[i] == 'u' || c[i] == 'x' || c[i] == 'X'
		|| c[i] == 'c' || c[i] == 's' || c[i] == '*' || c[i] == '0' || c[i] == '-'
		|| ft_isdigit(c[i]) || c[i] == '.' || c[i] == '%' || c[i] == '-' || c[i] == '0' || c[i] == '%'
		|| c[i] == ' ')
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
}*/

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

	i = 0;
	while (str[i])
	{
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'c' || str[i] == 's'
		|| str[i] == 'u' || str[i] == 'x'|| str[i] == 'X' || str[i] == 'p'
		|| str[i] == '0' || str[i] == '.' || str[i] == '-' || str[i] == '*'
		|| str[i] == '%')
			break ;
		i++;
	}
	return (str[i]);
}

size_t	ft_index(const char *str, const char *format)
{
	size_t i;

	i = 0;
	while (str[i + 1])
	{
		printf("str[i] %c\n", str[i]);
		if (str[i] == 'd' || str[i] == 'i' || str[i] == 'c' || str[i] == 's'
		|| str[i] == 'u' || str[i] == 'x'|| str[i] == 'X' || str[i] == 'p')
			break ;
		if (str[i] == '.' && (str[i + 1] == '*' || ft_isdigit(str[i + 1])))
		{
			i++;
			while(ft_isdigit(str[i + 1]))
				i++;
			break ;
		}
		if (str[i] == '*' && ft_isdigit(str[i + 1]) || (str[i] == '%'
		&& ft_isdigit(str[i + 1])))
		{
			while(ft_isdigit(str[i + 1]))
				i++;
			break ;
		}
		if (str[i] == '*')
			break ;
		if (str[i] == '0' || str[i] == '-')
			break ;
		i++;
	}
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
	printf("newstr %s\n", newstr);
	return (newstr);
}

const char	*extract_arg(size_t i, va_list args, char *format)
{
	if (ft_type(&format[i]) == 's')
		return (va_arg(args, char *));
	if (ft_type(&format[i]) == 'd' || ft_type(&format[i]) == 'i' ||
	ft_type(&format[i]) == 'c')
		return (ft_type(&format[i]) != 'c') ?
		ft_itoa(va_arg(args, int))
		: char_to_s((unsigned char)va_arg(args, int));
	if (ft_type(&format[i]) == 'u')
		return (ft_itoa(va_arg(args, unsigned int)));
	if (ft_type(&format[i]) == 'x' || ft_type(&format[i]) == 'X')
		return (to_hex(ft_type(&format[i]), va_arg(args, unsigned int),
		"0123456789abcdef"));
	if (ft_type(&format[i]) == 'p')
		return (ft_strjoin("0x", to_hex(ft_type(&format[i]),
		va_arg(args, unsigned int), "0123456789abcdef")));
	if (ft_type(&format[i]) == '.')
		return ((const char *)ft_precision(i, format, args));
	if (ft_type(&format[i]) == '*' || ft_type(&format[i]) == '%')
		return ((const char *)ft_spacing(i, format, args));
	if (ft_type(&format[i]) == '0')
		return (ft_strjoin("0", ""));
	if (ft_type(&format[i]) == '-')
		return (ft_strjoin("-", ""));
	i += ft_index(&format[i], format);
	printf("i = %zu\n", i);
}

const char *ft_spacing(size_t i, const char *format, va_list args)
{
	char *width;
	char *ret;

	width = "0";
	printf("FT_TYPE(&FORMAT[I + 1] %c\n", format[i + 1]);
	if (ft_isdigit(format[i + 1]))
	{
		ret = ft_strjoin("*", char_to_s(format[i + 1]));
		i++;
		while (ft_isdigit(format[i + 1]))
		{
			ret = ft_strjoin(ret, char_to_s(format[i + 1]));
			i++;
		}
		printf("ret 1 %s\n", ret);
		return (ret);
	}
	else
	{
		if(!(width = ft_itoa(va_arg(args, int))))
			return (char_to_s('0'));
		return (ft_strjoin("*", width));
	}
	return (0);
}

const char *ft_precision(size_t i, const char *format, va_list args)
{
	char *nb_char;
	char *ret;

	nb_char = "0";
	printf("FT_TYPE(&FORMAT[I + 1] %c\n", format[i + 1]);
	if (ft_isdigit(format[i + 1]))
	{
		ret = ft_strjoin(".", char_to_s(format[i + 1]));
		i++;
		while (ft_isdigit(format[i + 1]))
		{
			ret = ft_strjoin(ret, char_to_s(format[i + 1]));
			i++;
		}
		printf("ret 2 %s\n", ret);
		return (ret);
	}
	else
	{
		if(!(nb_char = ft_itoa(va_arg(args, int))))
			return (char_to_s('0'));
		return (ft_strjoin(".", nb_char));
	}
	return (0);
}

char *ft_fill_str(size_t nb_args, const char *format, va_list args)
{
	size_t i;
	size_t j;
	char **params;
	char **new_params;

	i = 0;
	j = 0;
	if (!(params = malloc(sizeof(char *) * 1024)))
		return (0);
	while (i + 2 < ft_strlen(format))
	{
		params[j] = ft_strjoin(extract_arg(i, args, format), "");
		i += ft_index(&format[i], format);
		j++;
	}
	params[j] = 0;
	new_params = ft_modify_strings(nb_args, 0, j, params);
	return (new_params);
}

const char **ft_modify_strings(size_t nb_args, size_t i, size_t j, char **params)
{
	size_t nb;
	size_t index;
	size_t value;
	char **upd_params;

	nb = 0;
	index = -1;
	if (!(upd_params = malloc(sizeof(char *) * (nb_args + 1))))
		return (0);
		while (i < j && nb < nb_args + 1)
		{
		if (params[i][0] == '.' && nb < nb_args + 1)
		{
			index = ft_find_arg(j, ++index, params);
			value = ft_atoi(&params[i][1]);
			if (value == 0)
				upd_params[nb][0] = '\0';
			else if (value - 1 < ft_strlen(params[index]))
			{
				upd_params[nb] = ft_strjoin(params[index], "");
				upd_params[nb][value] = '\0';
			}
			else if (value - 1 > ft_strlen(params[index]))
			{
				upd_params[nb] = ft_strjoin(replace_spaces(
				ft_spaces(value, params[index])), params[index]);
			}
			nb++;
		}
		if (i > 0 && (params[i][0] == '*' || params[i][0] == '%')
		&& params[i - 1][0] != '.' && nb < nb_args + 1)
		{
			printf("a\n");
			if (nb < nb_args + 1)
			{
			value = ft_atoi(&params[i][1]);
			upd_params[nb] = (value > ft_strlen(params[index])) ?
			ft_strjoin(ft_spaces(value, params[index]), params[index])
			: ft_strjoin(params[index], "");
			nb++;
			}
		}
		if (params[i][0] == '0' && nb < nb_args + 1)
		{
			index = ft_find_arg(j, ++index, params);
			upd_params[nb] = replace_spaces(params[index]);
			nb++;
		}
		if (params[i][0] == '-' && nb < nb_args + 1)
		{
			index = ft_find_arg(j, ++index, params);
			upd_params[nb] = ft_strjoin(params[index], ft_spaces(value,
			params[index]));
			nb++;
		}
		i++;
			}
		if (nb > 1)
		upd_params[nb - 1] = 0;
		else
			upd_params[nb] = 0;
		return (upd_params);
}

size_t ft_find_arg(size_t j, size_t find_index, char **params)
{
	size_t i;

	i = 0;
	while (find_index < j)
	{
		if (params[find_index][i] != '.' && params[find_index][i] != '*'
		&& params[find_index][i] != '0' && params[find_index][i] != '-')
			break ;
		find_index++;
	}
		return (find_index);
}

const char *replace_spaces(char *str)
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

const char *ft_spaces(size_t value, char *param)
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
