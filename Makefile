CC = gcc 
SRCS = ./srcs/malloc.c \
	   ./srcs/free.c \
	   ./srcs/realloc.c \
	   ./srcs/show_alloc_mem.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
INCDIRS = ./includes
CFLAGS = -Wall -Wextra -Werror -I$(INCDIRS) -g3
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME = libft_malloc_$(HOSTTYPE).so
ARCHIVE = libft_malloc_$(HOSTTYPE).a
LIBFT = ./libft/libft.a

all : $(NAME)

$(LIBFT) :
	make -C ./libft/

$(NAME) : $(ARCHIVE) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(ARCHIVE) $(LIBFT) -shared 
	ln -sf ./$(NAME) ./libft_malloc.so

$(ARCHIVE) : $(OBJS)
	ar -rcs $(ARCHIVE) $^

%.o : %.c
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $<

clean : 
	make clean -C ./libft/
	rm -rf $(ARCHIVE)
	rm -rf ./libft_malloc.so
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

test : t_malloc
	LD_PRELOAD=./libft_malloc.so ./test_malloc

t_malloc : $(NAME) $(LIBFT)
	$(CC) ./srcs/main.c -L./libft -lft -o test_malloc
	
tclean :
	rm -rf ./test_malloc

.PHONY : all clean fclean re test tclean
