#include "ft_printf.h"

int is_conv(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

void manage_characters(t_flag *help, char c, va_list args)
{
	char *res;
	int i;

	res = 0;
	i = 0;
	if (c == 's')
	{
		if (!(res = va_arg(args, char *)))
			help->ret += ft_putstr_len(c, "(null)", help);
		else
			help->ret += ft_putstr_len(c, res, help);
	}
	else
	{
		i = va_arg(args, int);
		help->ret += ft_putchar(i, help);
	}
}

void manage_hex(t_flag *help, char c, va_list args)
{
	unsigned int x;

	x = va_arg(args, unsigned int);
	if (x == 0)
		help->ret += ft_putstr_len(c, "0", help);
	else
		help->ret += ft_putstr_len(c, to_hex(c, x, "0123456789abcdef"), help);
}

void manage_pointers(t_flag *help, char c, va_list args)
{
	unsigned long long l;

	l = 0;
	if (!(l = (unsigned long long)va_arg(args, void *)) && (help->set_prec == 0 ||
		(help->set_prec == 1 && help->precision != 0)))
	{
		help->precision += 2;
		help->ret += ft_putstr_len(c, "0x0", help);
	}
	else if (!l)
		help->ret += ft_putstr_len(c, "0x", help);
	else
	{
		help->precision += 2;
		help->ret += ft_putstr_len(c, (char *)ft_strjoin("0x",
		to_hex(c, l, "0123456789abcdef")), help);
	}
}

void manage_numbers(t_flag *help, char c, va_list args)
{
	int type;

	type = 0;
	if (c == 'd' || c == 'i')
	{
		type = va_arg(args, int);
		help->ret += ft_putstr_len(c, ft_itoa(type), help);
	}
	else if (c == 'u')
	{
		type = va_arg(args, int);
		if (type > 0)
			help->ret += ft_putstr_len(c, ft_itoa(type), help);
		else
			help->ret += ft_putstr_len(c, ft_itoa_u(type), help);
	}
}
