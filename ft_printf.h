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
char	**ft_order_params(size_t j, const char *params, const char *format);
const void	*ft_memmove(const void *dst, const void *src, size_t len);
const char		*ft_itoa(int n);
int	ft_atoi(const char *str);
size_t	ft_nb_params(const char *format);
char	ft_type(const char *str);
size_t	ft_index(const char *str, const char *format);
char	*char_to_s(int x);
char	*to_hex(char c, unsigned int n, char *base);
char	*revstr(char *str);
char *str_toupper(char *str);
const char	*extract_arg(size_t i, const char *str, va_list args, char *format);
char			**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
char **ft_rewrite_format(const char *format);
char *ft_replace_format(char **new_format, const char *format, char *n_format);
int             ft_is_value(char c);
char *ft_fill_str(char *str, const char *format, va_list args);
const char *ft_precision(size_t i, const char *format, va_list args);
const char *ft_spacing(size_t i, const char *format, va_list args);
const char	*join_three(const char *s1, const char *s2, const char *s3);

#endif
