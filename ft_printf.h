#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
#include <stddef.h>

int	ft_printf(const char *format, const char *params);
int		check_format(const char *format);
int	ft_isdigit(int c);
size_t	ft_strlen(const char *s);
const char	*ft_strjoin(const char *s1, const char *s2);
const char	*find_param(const char *format, const char *params);
const void	*ft_memmove(const void *dst, const void *src, size_t len);

#endif
