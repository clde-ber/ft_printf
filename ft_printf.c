#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	const char *str;
	char *n_format;
	const char **tab;
	size_t i;
	size_t j;
	va_list	args;

	n_format = ft_replace_format(ft_rewrite_format(format), format, n_format);
	printf("n_fromat%s\n", n_format);
	j = 0;
	i = 0;
	printf("format ! %s\n", format);
	va_start(args, format);
	str = ft_strjoin("", "");
	while (i < ft_strlen(n_format) && ft_format(n_format))
	{
		str = ft_strjoin(extract_arg(i, str, args, n_format), ",");
		str = (j != 0) ? ft_strjoin(str, extract_arg(i, str, args, n_format)) : str;
		i += ft_index(&n_format[i], n_format);
		j++;
		printf("STR %s\n", str);
		printf("i %zu\n", i);
	}
	printf("J %zu\n", j);
	printf("str %s\n", str);
	tab = ft_order_params(j, str, n_format);
	printf("tab[0] %s\n", tab[0]);
	printf("tab[1] %s\n", tab[1]);
	printf("tab[2] %s\n", tab[2]);
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
