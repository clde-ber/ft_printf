#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	const char *str;
	size_t i;
	size_t nb_params;
	va_list	args;


	i = 0;
	nb_params = 0;
	va_start(args, format);
	str = ft_strjoin("", "");
	while (format[i++])
		if (format[i] == '*' || format[i] == '%')
			nb_params++;
	i = 0;
	while (i < nb_params)
	{
		str = ft_strjoin(str, ft_itoa(va_arg(args, int)));
		if (i < nb_params)
			str = ft_strjoin(str, ", ");
		printf("str %s\n", str);
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
