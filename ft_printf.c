#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	char *n_format;
	const char **tab;
	size_t i;
	size_t j;
	size_t nb_args;
	va_list	args;

	j = -1;
	i = 0;
	nb_args = 0;
	printf("format ! %s\n", format);
	va_start(args, format);
	while (format[++j])
		if (format[j] == '%')
			nb_args++;
	printf("NB ARGS %zu\n", nb_args);
	tab = ft_fill_str(nb_args, format, args);
	while (tab[i])
	{
		ft_putstr(tab[i]);
		i++;
	}
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
