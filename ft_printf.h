#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>

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
char	ft_type(const char *str, const char *format);
size_t	ft_index(const char *str, const char *format);
char	*char_to_s(int x);
char	*to_hex(char c, unsigned int n, char *base);
char	*revstr(char *str);
char *str_toupper(char *str);
const char	*extract_arg(size_t i, va_list args, const char *format);
char			**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
char **ft_rewrite_format(const char *format);
char *ft_replace_format(char **new_format, const char *format, char *n_format);
int             ft_is_value(char c);
const char **ft_fill_str(size_t nb_args, const char *format, va_list args);
const char *ft_precision(size_t i, const char *format, va_list args);
const char *ft_spacing(size_t i, const char *format, va_list args);
char **ft_modify_strings(size_t nb_args, size_t i, size_t j, char **params);
const char *replace_spaces(char *str);
const char *ft_spaces(size_t value, char *param);
size_t ft_find_arg(size_t j, size_t find_index, char **params);
int check_conv(size_t i, const char *format);
int ft_is_conv(char c);
void ft_putchar(char c);
void ft_putstr(char *str);

#endif
