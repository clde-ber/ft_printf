#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int i;
	int j;
	int x;
	int ret;
	int nb_args;
	va_list args;
	char **tab;

	i = 0;
	j = 0;
	x = 0;
	nb_args = 0;
	ret = 0;
	while (format[j])
	{
		if (format[j] == '%')
			nb_args++;
		j++;
	}
	if (!(tab = malloc(sizeof(char *) * (j + 1))))
		return (0);
	j = 0;
	va_start(args, format);
	while (format[j])
	{
		while (ft_isdigit(format[j]) && check_conv(j, format))
		j++;
		tab[i] = (char *)extract_arg(j, args, format);
	//	printf("tab[i]%s\n", tab[i]);
		if (format[j] != '%' || (format[j] == '%' && format[j + 1] == '%'))
			i++;
		j++;
	}
	tab[i] = 0;
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (tab[i][0] == 'f' && (tab[i][1] == '0' || tab[i][1] == '.' || tab[i][1] == '*' || tab[i][1] == '-'))
			tab[i] = ft_modify(j, tab, tab[i]);
		while (tab[i][x])
		{
			if (tab[i][x] != '@' && tab[i][0] != 'f')
			{
			//	printf("x = %d\n", x);
			//	printf("i = %d\n", i);
			//	printf("tab[i][x] %c\n", tab[i][x]);
				ft_putchar(tab[i][x]);
			//	printf("tab[i]%s\n", tab[i]);
				ret++;
			}
			x++;
		}
		i++;
		x = 0;
	}
	va_end(args);
	return (ret);
}
