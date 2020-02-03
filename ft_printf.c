#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	const char **tab;
	size_t i;
	size_t j;
	int nb_args;
	va_list	args;

	j = -1;
	i = 0;
	nb_args = 0;
	va_start(args, format);
	while (format[++j])
	{
		if (format[j] == '%')
		{
			nb_args++;
			if (nb_args == 1)
				i = j;
		}
		if (nb_args == 0)
		ft_putchar(format[j]);
	}
	tab = ft_fill_str(nb_args, &format[i], args);
	i = 0;
	while (i + 1 < nb_args)
	{
		ft_putstr(tab[i]);
		i++;
	}
	j = -1;
	while (format[++j] && nb_args)
		if (format[j] == '%')
			nb_args--;
		while (format[j] == '.' || format[j] == '*' || format[j] == '0'
		|| format[j] == '-' || format[j] == 'd' || format[j] == 'i' ||
		format[j] == 'c' || format[j] == 's' || format[j] == 'u' ||
		format[j] == 'x'|| format[j] == 'X' || format[j] == 'p')
			j++;
	ft_putstr(&format[j]);
	va_end(args);
	return (0);
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
