#include "ft_printf.h"
int main()
{
	ft_printf("%d%d%c", 25631654, -1000000, 'a');
	unsigned int i;

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
