#include "ft_printf.h"

int write_minus(int k, char c, const char *str, t_flag *help)
{

	if (help->rev == 0)
	{
		if (c != 's' && str[k] == '-' && (help->set_prec == 0 || (help->set_prec == 1 &&
			help->precision >= 1)))
		{
			write(1, "-", sizeof(char));
			return (1);
		}
	}
	else
	{
		if (str[k] == '-' && (help->set_prec == 0 || (help->set_prec == 1 &&
			help->precision >= 1)))
		{
			write(1, "-", sizeof(char));
			return (1);
		}
	}
	return (0);
}

int write_address(int k, const char *str)
{
	if (str[k] == '0' && str[k + 1] == 'x')
	{
		write(1, "0x", sizeof(char) * 2);
		return (2);
	}
	return (0);
}

int write_string(int k, char c, const char *str, t_flag *help)
{
	int i;

	i = 0;
	while ((str[k + i] && k + i < help->precision && help->set_prec &&
		help->precision != -1) || (str[k + i] && (help->set_prec == 0 ||
		(help->set_prec == 1 && help->precision == -1))) || (str[k + i] && (c == 'p'
		|| c == 'i' || c == 'd' || c == 'x' || c == 'X' || c == 'u')))
	{
		if (help->set_prec == 1 && help->precision == 0 &&
		str[k + i] == '0' && ft_strlen(str)	== 1 && c != 's' && help->bool_3 == 0)
			write(1, " ", sizeof(char));
		else if ((str[k + i] == '0' && ft_strlen(str) == 1 && help->set_prec == 1 &&
			help->precision == 0 && c != 's') || help->bool_3)
			help->ret--;
		else
			write(1, &str[k + i], sizeof(char));
		i++;
	}
	return (i);
}

void write_others_rev(int k, const char *str, t_flag *help)
{
	if (help->set_prec == 1 && help->precision == 0 && str[k] == '0' && ft_strlen(str)
	== 1 && help->bool_3 == 0)
		write(1, " ", sizeof(char));
	else if ((str[k] == '0' && ft_strlen(str) == 1 && help->set_prec == 1 &&
	help->precision == 0) || help->bool_3)
		help->ret--;
	else
		write(1, &str[k], sizeof(char));
}

int write_string_rev(int k, const char *str, t_flag *help)
{
	int i;

	i = 0;
	while ((str[k + i] && k + i < help->precision && help->set_prec &&
	help->precision != -1) || (str[k + i] && (help->set_prec == 0 ||
	(help->set_prec == 1 && help->precision == -1))))
	{
		write(1, &str[k + i], sizeof(char));
		i++;
	}
	return (i);
}
