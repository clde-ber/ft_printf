#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int i;
	int ret;
	va_list args;
	t_flag help;

	i = 0;
	ret = 0;
	init_struct(&help);
	va_start(args, format);
	while (i < ft_strlen(format))
	{
		if (i >= ft_strlen(format))
			break ;
//		i += find_percent(&format[i]);
	//	printf("findpercent %d\n", find_percent(&format[i]));
		while (format[i] && (find_percent(&format[i]) > 1 || !find_percent(&format[i])))
		{
			ft_putchar(format[i]);
			help.ret++;
			i = (find_percent(&format[i])) ? i + find_percent(&format[i]) : ++i;
		}
		if (format[i] && find_percent(&format[i]) == 1)
		{
			fill_struct(&help, i, &format[i], args);
			i += find_index(i + 1, format);
		}
	}
	va_end(args);
	return (help.ret);
}
