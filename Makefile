SRCS		= ft_printf.c\
		ft_printf_utils.c

OBJ		= $(SRCS:.c=.o)
NAME		= libftprintf.a
CC		= gcc
RUN_SRC		= -c
INCL		= -include
HEADER		= ft_printf.h
LIB		= ar -rcs
RM		= rm -f
CFLAGS		= -Wall -Wextra -Werror
.c.o:
		@$(CC) $(RUN_SRC) $(CFLAGS) $(SRCS) $(INCL) $(HEADER)
$(NAME):	$(OBJ)
		@$(LIB) $(NAME) $(OBJ)
all:		$(NAME)
clean:
		@$(RM) $(OBJ)
fclean:		clean
		@$(RM) $(NAME)
re:		fclean all
.PHONY:		all clean fclean re
