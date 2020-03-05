void update_flags(char c, const char *str, t_flag *help)
{
	help->rev = (help->width < 0) ? 1 : help->rev;
	help->bool_1 = (help->width < 0) ? 1 : help->bool_1;
	help->width = (help->width < 0) ? -help->width : help->width;
	help->bool_3 = (str[0] == '0' && ft_strlen(str) == 1 && help->set_prec == 1 &&
		help->precision == 0 && help->width < 1 && c != 's' && help->bool_1 == 0) ? 1 :
		help->bool_3;
	help->zero = ((help->precision > ft_strlen(str) && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
		|| c == 'x' || c == 'X'))) ? 1 : help->zero;
	help->precision = (help->precision < 0) ? -1 : help->precision;
	help->set_prec = (help->precision < 0) ? 1 : help->set_prec;
	help->width = (help->width <= ft_strlen(str) && (c == 'i' || c == 'd' || c == 'u' || c == 'p'
		|| c == 'x' || c == 'X')) ? 0 : help->width;
	help->precision = (help->width == ft_strlen(str) && help->precision > ft_strlen(str)) ?
		ft_strlen(str) : help->precision;
	help->precision = (c == 's' && help->precision > ft_strlen(str)) ? ft_strlen(str) :
		help->precision;
	if (c != 's' && help->zero == 1 && help->width > ft_strlen(str) && help->precision == -1)
	{
		help->precision = (str[0] == '-') ? help->width - 1 : help->width;
		help->width = 0;
		help->bool_2 = 1;
	}
	if (c != 's' && str[0] == '-')
		help->precision++;
}

int width_len_conditions_standard(int j, char c, const char *str, t_flag *help)
{
	if ((((j < help->width - ft_strlen(str) && (help->precision == -1 ||
	help->set_prec == 0)) || (j < help->width - help->precision  &&
	help->set_prec == 1 && help->precision != -1 && help->precision < help->width))
	&& c == 's') || (c != 's' && ((j < help->width - ft_strlen(str)
	&& (help->set_prec == 0 || (help->set_prec == 1 && (help->precision <= ft_strlen(str) &&
	help->precision != 0)) || (j < help->width - help->precision && help->precision < help->width
	&& ((help->precision == 0 && help->set_prec == 1) || (help->precision >	ft_strlen(str)))))))))
		return (1);
	return (0);
}

int ft_putstr_len_standard(int i, char c, const char *str, t_flag *help)
{
	int j;
	int k;

	j = -1;
	k = 0;
	while (width_len_conditions_standard(++j, c, str, help))
	{
		k = (j == 0 && ((help->zero == 1 && (help->set_prec == 0 ||
		help->precision == -1)) || help->bool_1)) ? k + write_minus(k, c, str, help) : k;
 		help->waste = ((help->zero == 1 && (help->set_prec == 0 || help->precision == -1))
			|| help->bool_1) ? write(1, "0", sizeof(char)) : write(1, " ", sizeof(char));
	}
	k += write_minus(k, c, str, help);
	while (++i < help->precision - ft_strlen(str))
	{
		k = (i == 0) ? k + write_address(k, str) : k;
		help->waste = (c != 's') ? write(1, "0", sizeof(char)) : write(1, " ", sizeof(char));
	}
	k += write_minus(k, c, str, help);
	k += write_string(k, c, str, help);
	return (i + j + k);
}

int ft_putstr_len_rev(int i, char c, const char *str, t_flag *help)
{
	int j;
	int k;

	j = -1;
	k = 0;
	k += write_minus(k, c, str, help);
	k = (c == 's') ? k + write_string_rev(k, str, help) : k;
	while (++i < help->precision - ft_strlen(str) && help->bool_2 == 0)
	{
		k = (i == 0) ? k + write_address(k, str) : k;
		help->waste = (c != 's') ? write(1, "0", sizeof(char)) : write(1, " ", sizeof(char));
	}
	while (str[k] && c != 's')
	{
		write_others_rev(k, str, help);
		k++;
	}
	while (i < help->precision - ft_strlen(str) && help->bool_2)
	{
		k = (++i - 1 == 0) ? k + write_address(k, str) : k;
		write(1, " ", sizeof(char));
	}
	while (++j + k + i < help->width)
		write(1, " ", sizeof(char));
	return (j + k + i);
}

int ft_putstr_len(char c, const char *str, t_flag *help)
{
	update_flags(c, str, help);
	if (help->rev == 0)
		return (ft_putstr_len_standard(-1, c, str, help));
	else
		return (ft_putstr_len_rev(-1, c, str, help));
}
