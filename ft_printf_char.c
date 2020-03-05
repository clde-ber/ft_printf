#include "ft_printf.h"

static void update_flags_char(t_flag *help)
{
	if (help->width < 0)
	{
		help->bool_1 = 1;
		help->rev = 1;
		help->width = -help->width;
	}
	if (help->precision < 0)
	{
		help->precision = -1;
		help->set_prec = 1;
	}
	if (help->width <= 1)
		help->width = 0;
	if (help->width == 1 && help->precision > 1)
		help->precision = 1;
	if (help->precision > 1)
		help->precision = 1;
}

static int width_len_conditions(t_flag *help, int j, char c)
{
	if ((j < help->width - 1 && (help->precision == -1 || help->set_prec == 0)) ||
		(((j < help->width - help->precision && help->set_prec == 1 && help->precision != -1
		&& help->precision < help->width)) && c == 'c') || (c != 'c' && ((j < help->width - 1 &&
		(help->set_prec == 0 || (help->set_prec == 1 && (help->precision <= 1 && help->precision != 0))
		|| (j < help->width - help->precision && help->precision < help->width && ((help->precision == 0
		&& help->set_prec == 1) || (help->precision > 1))))))))
			return (1);
	return (0);
}

static void write_space_o_zero_char(t_flag *help)
{
	if ((help->zero == 1 && (help->set_prec == 0 || help->precision == -1))
		|| help->bool_1)
		write(1, "0", sizeof(char));
	else
		write(1, " ", sizeof(char));
}


int ft_putchar(char c, t_flag *help)
{
	int i;
	int j;

	i = -1;
	j = -1;
	update_flags_char(help);
	if (help->rev == 0)
	{
		while (width_len_conditions(help, ++j, c))
			write_space_o_zero_char(help);
		while (++i < help->precision - 1)
			write(1, " ", sizeof(char));
		write(1, &c, sizeof(char));
	}
	else
	{
		write(1, &c, sizeof(char));
		while (++i < help->precision - 1)
			write(1, " ", sizeof(char));
		while (++j + i + 1 < help->width)
			write(1, " ", sizeof(char));
	}
	return (j + i + 1);
}
