#include "ft_printf.h"
int main()
{
	ft_printf("%d%X%x\n", 25631654, 1000000, 2358);
	printf("%d%X%x\n", 25631654, 1000000, 2358);
	printf("%d\n", ft_printf("ultimate %*.*d     *.*s\n", 1, 50, 5000, 1, 0, "hey"));
	printf("%d\n", printf("ultimate %*.*d     *.*s\n", 1, 50, 5000, 1, 0, "hey"));
	printf("ret = %d\n", printf("%%p::[%1.50d]\n", 8473));
	printf("ret = %d\n", ft_printf("%%p::[%1.50d]\n", 8473));
//	printf("%d\n\n", printf("15unsigned 1 %.u unsigned 2 %.u\n\n", 42, -42));
//	printf("%d\n\n", ft_printf("15unsigned 1 %.u unsigned 2 %.u\n\n", 42, -42));
/*	i = 400000;
	printf("%d", i);
	printf("sizeof int %d\n", sizeof(int));
	printf("sizeof char %d\n", sizeof(char));
	printf("sizeof char * %d\n", sizeof(char *));
	printf("sizeof uint %d\n", sizeof(unsigned int));
	printf("sizeof ulong %d\n", sizeof(unsigned long));
	printf("sizeof unsigned char %d\n", sizeof(unsigned char));
*/
	return (0);
}/*
int		main(int ac, char **av)
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
