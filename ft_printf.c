#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int i;
	int ret;
	int boolean;
	va_list args;
	t_flag help;

	i = 0;
	ret = 0;
	boolean = 0;
	init_struct(&help);
	va_start(args, format);
	while (i < ft_strlen(format))
	{
		if (i == ft_strlen(format) - 1)
			break ;
		while (format[i] && !(find_percent(&format[i])))
		{
			ft_putchar(format[i]);
			help.ret++;
			i++;
		}
		if (find_percent(&format[i]) && boolean == 0)
		{
			fill_struct(&help, i, &format[i], args);
			i = find_index(++i, format);
			boolean = 1 ;
		}
		boolean = 0;
	}
	va_end(args);
	return (help.ret);
}
