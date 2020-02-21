#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int i;
	int ret;
	int j;
	va_list args;
	t_flag help;

	i = 0;
	j = 0;
	ret = 0;
	init_struct(&help);
	va_start(args, format);
	while (find_index(i, format) != -1)
	{
	//	printf("i = %d\n", i);
		if (format[i] == '%' && format[i + 1] != '%')
		{
			fill_struct(&help, &format[i], args);
			i = find_index(++i, format);
			init_all_except_ret(&help);
		}
		else
		{
			if (format[i] == '%' && format[i + 1] == '%')
			{
				i++;
				ft_putchar(format[i], &help);
			}
			if (format[i] != '%')
			{
				ft_putchar(format[i], &help);
			}
			i++;
		}
	}
	va_end(args);
	return (help.ret + 1);
}
