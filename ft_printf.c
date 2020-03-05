#include "ft_printf.h"

void		init_struct(t_flag *help)
{
	help->width = 0;
	help->precision = 0;
	help->set_prec = 0;
	help->rev = 0;
	help->zero = 0;
	help->ret = 0;
	help->bool_1 = 0;
	help->bool_2 = 0;
	help->bool_3 = 0;
	help->waste = 0;
}

void		init_all_except_ret(t_flag *help)
{
	help->width = 0;
	help->precision = 0;
	help->set_prec = 0;
	help->rev = 0;
	help->zero = 0;
	help->bool_1 = 0;
	help->bool_2 = 0;
	help->bool_3 = 0;
	help->waste = 0;
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

void fill_struct_conv(t_flag *help, char c, va_list args)
{
	if (c == 's' || c == 'c')
		manage_characters(help, c, args);
	else if (c == 'd' || c == 'i' || c == 'u')
		manage_numbers(help, c, args);
	else if (c == 'x' || c == 'X')
		manage_hex(help, c, args);
	else if (c == 'p')
		manage_pointers(help, c, args);
}

int	ft_printf(const char *format, ...)
{
	int i;
	va_list args;
	t_flag help;

	i = 0;
	init_struct(&help);
	va_start(args, format);
	while (format[i])
		if (format[i] == '%' && format[i + 1] != '%')
		{
			fill_struct(&help, &format[i], args);
			i = find_index(++i, format);
		}
		else
		{
			if (format[i] == '%' && format[i + 1] == '%')
			 	help.ret += write(1, &format[++i], sizeof(char));
			if (format[i] != '%')
				help.ret += write(1, &format[i], sizeof(char));
			i++;
		}
	va_end(args);
	return (help.ret);
}
