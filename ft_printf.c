#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	const char *str;
	size_t i;
	va_list	args;

	i = 0;
	va_start(args, format);
	str = ft_strjoin("", "");
	while (i < ft_strlen(format) && ft_format(format))
	{
		if (ft_find_type(&format[i]) == 's')
			str = ft_strjoin(str, va_arg(args, char *));
		if (ft_find_type(&format[i]) == 'd' || ft_find_type(&format[i]) == 'i'
		|| ft_find_type(&format[i]) == 'c')
			str = (ft_find_type(&format[i]) != 'c') ? ft_strjoin(str, ft_itoa(va_arg(args, int)))
			: ft_strjoin(str, char_to_s((unsigned char)va_arg(args, int)));
		if (ft_find_type(&format[i]) == 'u')
			str = ft_strjoin(str, ft_itoa(va_arg(args, unsigned int)));
		if (ft_find_type(&format[i]) == 'x' || ft_find_type(&format[i]) == 'X')
			str = ft_strjoin(str, to_hex(va_arg(args, unsigned int), "0123456789abcdef"));
		if (ft_find_type(&format[i]) == 'p')
			str = ft_strjoin(str, ft_itoa(va_arg(args, int)));
		i += ft_index(&format[i], format);
		str = (i != ft_strlen(format)) ? ft_strjoin(str, ", ") : str;
		printf("%zu\n", i);
		printf("str %s\n", str);
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
