#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		res;
	const char *str;
	size_t i;
	void *ptr;

	i = 0;
	ptr = args;
	write(1, "a", 1);
	write(1, "a", 1);
	va_start(args, format);
	str = ft_strjoin("","");
	str = ft_strjoin(ft_convert(args), "");
	printf("string 1 %s\n", str);
	while (i < 6)
	{
		str = ft_strjoin(str, ft_convert(args));
		str = ft_strjoin(str, args);
		va_arg(args, char *);
		printf("%s\n", str);
		write(1, "a", 1);
		i++;
	}
	va_end(args);
	return (res);
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
