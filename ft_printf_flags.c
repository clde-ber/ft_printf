#include "ft_printf.h"

int is_flag(const char c)
{
	if (c == '.' || c == '-' || c == '*' || ft_isdigit(c))
		return (1);
	return (0);
}

static int record_flags(int j, t_flag *help, const char *format)
{
	if (format[j] == '-')
		help->rev = 1;
	if (format[j] == '0')
	{
		if (format[j + 1] == '-' || (j > 0 && format[j - 1] == '-'))
			help->rev = 1;
		else
		{
			help->zero = 1;
			help->rev = 0;
		}
	}
	j++;
	return (j);
}

static int record_width(int j, t_flag *help, const char *format, va_list args)
{
	if (format[j] != '*')
	{
		help->width = ft_atoi(&format[j]);
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
			while (ft_isdigit(format[j]) || format[j] == '-')
				j++;
		}
	}
	return (j);
}

static int record_precision(int j, t_flag *help, const char *format, va_list args)
{
	help->set_prec = 1;
	if (format[j + 1] == '*' || ft_isdigit(format[j + 1]))
	{
		j++;
		while (ft_isdigit(format[j]) || format[j] == '-')
		{
			help->precision = ft_atoi(&format[j]);
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
		j++;
	}
	return (j);
}


void fill_struct(t_flag *help, const char *format, va_list args)
{
	int j;

	j = 1;
	while (format[j] && (is_flag(format[j]) || is_conv(format[j])))
	{
		while (format[j] == '-' || format[j] == '0')
			j = record_flags(j, help, format);
		if (format[j] == '*' || ft_isdigit(format[j]))
	  		j = record_width(j, help, format, args);
		if (format[j] == '.')
			j = record_precision(j, help, format, args);
		if (format[j] == '%')
		{
			help->ret += ft_putchar(format[j], help);
			init_all_except_ret(help);
		}
		else if (is_conv(format[j]))
		{
			fill_struct_conv(help, format[j], args);
			init_all_except_ret(help);
		}
		j++;
		while (is_flag(format[j]) || is_conv(format[j]))
		{
			help->ret++;
			write(1, &format[j], sizeof(char));
			j++;
		}
		break ;
	}
}
