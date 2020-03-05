#include "ft_printf.h"

char	*revstr(char *str)
{
	size_t i;
	size_t j;
	char *newstr;

	j = 0;
	i = ft_strlen(str) + 1;
	if (!(newstr = malloc(sizeof(char) * i)))
		return (0);
	while (i - 1 > 0)
	{
		newstr[j] = str[--i - 1];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*to_hex(char c, unsigned long long n, char *base)
{
	int i;
	char *str;
	unsigned long long k;

	k = n;
	i = 0;
	while (k > 0)
	{
		k = k / ft_strlen(base);
		i++;
	}
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (n > 0)
	{
		str[i] = base[n % ft_strlen(base)];
		n = n / ft_strlen(base);
		i++;
	}
	str[i] = '\0';
	str = revstr(str);
	if (c == 'X')
		str = str_toupper(str);
//	printf("to hex %s\n", str);
	return (str);
}
