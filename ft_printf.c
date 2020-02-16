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
		while (i > 0 && ft_isdigit(format[j]) && check_conv(j, format))
		j++;
		tab[i] = (char *)extract_arg(j, args, format);
	//	printf("1 - tab[i]%s\n", tab[i]);
		if (format[j] != '%' || (format[j] == '%' && format[j + 1] == '%'))
			i++;
		if (format[j] == '%' && (format[j + 1] == '*' || format[j + 1] == '.') && (format[j + 2] == 'c' || format[j + 2] == 's' ||
			format[i + 2] == 'd' || format[i + 2] == 'i' || format[i + 2] == 'u' || format[i + 2] == 'p'
			|| format[i + 2] == 'x' || format[i + 2] == 'X'))
		{
			i++;
			j++;
		}
		j++;
	}
	tab[i] = 0;
	i = 0;
	j = 0;
	while (tab[i] && i + 1 < ft_strlen(format))
	{
	//	printf("i%d\n", i);
		if (tab[i][0] == 'f' && (tab[i][1] == '0' || tab[i][1] == '.' || tab[i][1] == '*' || tab[i][1] == '-'))
		{
			j += find_arg(j, tab);
			tab[j] = ft_modify(j, tab, tab[i]);
		}
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
	//		printf("2 - tab[i]%s\n", tab[i]);
	//	printf("%d\n", i);
		i++;
		x = 0;
	}
	va_end(args);
	return (ret);
}
