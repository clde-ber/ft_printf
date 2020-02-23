#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_flag
{
		int		width;
		int		precision;
		int		set_prec;
		int		rev;
		int		zero;
		int 	ret;
}				t_flag;

int			ft_printf(const char *format, ...);
int 		ft_putstr_len(const char *str, t_flag *help);
int ft_putstr(const char *str);
int ft_putchar(char c, t_flag *help);
char	*to_hex(char c, unsigned int n, char *base);
int	ft_atoi(const char *str);
const char		*ft_itoa_u(unsigned int n);
const char		*ft_itoa(int n);
const void	*ft_memmove(const void *dst, const void *src, size_t len);
const char	*join_a_free(const char *s1, const char *s2);
const char	*ft_strjoin(const char *s1, const char *s2);
int	ft_strlen(const char *s);
int	ft_isdigit(int c);
void fill_struct_conv(t_flag *help, char c, va_list args);
void fill_struct(t_flag *help, const char *format, va_list args);
int find_index(int i, const char *str);
int is_conv(const char c);
int is_flag(const char c);
int		find_percent(const char *str);
void		init_struct(t_flag *help);
void		init_all_except_ret(t_flag *help);
char *str_toupper(char *str);
char	*revstr(char *str);

#endif
