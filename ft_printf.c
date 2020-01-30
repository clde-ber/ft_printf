#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	const char *str;
	char *n_format;
	const char **tab;
	size_t i;
	size_t j;
	va_list	args;

	j = 0;
	i = -1;
	printf("format ! %s\n", format);
	va_start(args, format);
	str = ft_strjoin("", "");
	str = ft_fill_str(str, format, args);
	tab = ft_split(str, ',');
	printf("%s\n", str);
	while (tab[++i])
		printf("tab[i] = %s\n", tab[i]);
	printf("J %zu\n", j);
	printf("str %s\n", str);
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
