NAME = 	libft.a
CC = gcc
INCDIRS = ./includes
CFLAGS = -Wall -Wextra -Werror -I$(INCDIRS) -g3
CFILES = ./convert/ft_atoi.c ./convert/ft_itoa.c ./convert/ft_atoll.c ./list/ft_lstnew.c ./list/ft_lstadd_front.c ./list/ft_lstsize.c ./list/ft_lstlast.c ./list/ft_lstadd_back.c ./list/ft_lstdelone.c ./list/ft_lstclear.c ./list/ft_lstiter.c ./list/ft_lstmap.c ./mem/ft_bzero.c ./mem/ft_calloc.c ./mem/ft_memchr.c ./mem/ft_memcmp.c ./mem/ft_memcpy.c ./mem/ft_memmove.c ./mem/ft_memset.c ./put/ft_putchar_fd.c ./put/ft_putendl_fd.c ./put/ft_putnbr_fd.c ./put/ft_putstr_fd.c ./string/ft_isalpha.c ./string/ft_isdigit.c ./string/ft_isalnum.c ./string/ft_isascii.c ./string/ft_isprint.c ./string/ft_split.c ./string/ft_strchr.c ./string/ft_strdup.c ./string/ft_strcmp.c ./string/ft_striteri.c ./string/ft_strjoin.c ./string/ft_strlcat.c ./string/ft_strlcpy.c ./string/ft_strlen.c ./string/ft_strmapi.c ./string/ft_strmapi.c ./string/ft_strncmp.c ./string/ft_strnstr.c ./string/ft_strrchr.c ./string/ft_strtrim.c ./string/ft_substr.c ./string/ft_tolower.c ./string/ft_toupper.c ./ft_printf/ft_hexa.c ./ft_printf/ft_numbers.c ./ft_printf/ft_pointer.c ./ft_printf/ft_printf.c ./ft_printf/ft_printpc.c ./ft_printf/ft_string.c ./gnl/get_next_line.c ./convert/ft_atod.c
OBJS = $(patsubst %.c,%.o,$(CFILES))

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean :
	rm -rf $(OBJS) $(OBJSBNS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
