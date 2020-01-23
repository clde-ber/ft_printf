
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int		ft_format(const char *format);
int	ft_isdigit(int c);
int	ft_strlen(const char *s);
const char	*ft_strjoin(const char *s1, const char *s2);
const char	*find_param(const char *format, const char *params);
const void	*ft_memmove(const void *dst, const void *src, size_t len);
const char		*ft_itoa(int n);
int	ft_atoi(const char *str);
size_t	ft_nb_params(const char *format);
char	ft_find_type(const char *str);
size_t	ft_index(const char *str, const char *format);
char	*char_to_s(int x);

#endif
