#include "ft_printf.h"

int	ft_printf(const char *format, const char *params)
{
	int i;
	int j;
	const char **stock;
	const char *output;
	int	*fct_ptr;

	i = -1;
	j = -1;
	/*while (format[++i])
	{
		if (check_format(format))
			if (find_conv_o_flag(format[i]))
			{
				fct_ptr = find_conv_o_flag(format[i]);
				stock[j] = find_param(format, str);
				stock[j] = app_fct(stock[j], &fct_ptr);
				j++;
			}
		else
			return 0;
	}
	stock[j] = 0;
	while (stock[j])
		output = (j == 0) ? ft_strjoin(stock[j], "") : ft_strjoin(output, stock[j]);
	return (ft_strlen(output));*/
//	printf("%d\n", check_format(format));
	printf("%s\n", params);
	printf("%s\n", find_param(format, params));
}
