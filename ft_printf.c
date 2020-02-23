#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int i;
	int boolean;
	va_list args;
	t_flag help;

	i = 0;
	boolean = 0;
	init_struct(&help);
	va_start(args, format);
	while (find_index(i, format) != -1)
	{
	//	printf("i = %d\n", i);
		if (format[i] == '%' && format[i + 1] != '%' && boolean == 0)
		{
			fill_struct(&help, &format[i], args);
			i = find_index(++i, format);
			init_all_except_ret(&help);
			boolean = 1;
		}
		else
		{
			if (format[i] == '%' && format[i + 1] == '%')
			{
				i++;
				write(1, &format[i], sizeof(char));
				help.ret++;
			}
			if (format[i] != '%')
			{
				write(1, &format[i], sizeof(char));
				help.ret++;
			}
			boolean = 0;
			i++;
		}
	}
	va_end(args);
	return (help.ret);
}
