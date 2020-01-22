#include "ft_printf.h"
int main()
{
	ft_printf("hellos", "toi", "ca", "va");
	return (0);
}
/*int		main(int ac, char **av)
{
	(void)ac;
	size_t i;
	const char *format = "%s\n";
	const char *params;

	i = 1;
	while (av[i + 1])
	{
		params = (i == 1) ? ft_strjoin(av[i], av[i + 1]) : ft_strjoin(params, av[i + 1]);
//		printf(format, params);
		i++;
	}
	ft_printf(format, "hello", "toi", "ca", "va");
//	printf("params %s\n", params);
	return (0);
}*/
