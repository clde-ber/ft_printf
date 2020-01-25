#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	const char *str;
	char **test;
	char *n_format;
	const char **tab;
	size_t i;
	size_t j;
	va_list	args;

	test = ft_rewrite_format(format);
	printf("%s\n", test[0]);
	printf("%s\n", test[1]);
	printf("%s\n", test[2]);
	n_format = ft_replace_format(ft_rewrite_format(format), format, n_format);
	i = 0;
	j = 0;
	va_start(args, format);
	str = ft_strjoin("", "");
	while (i < ft_strlen(format) && ft_format(format))
	{
		str = extract_arg(i, str, args, format);
		i += ft_index(&format[i], format);
		str = (i != ft_strlen(format)) ? ft_strjoin(str, ",") : str;
		j++;
		printf("%zu\n", i);
		printf("str %s\n", str);
	}
	tab = ft_order_params(j, str, format);
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
