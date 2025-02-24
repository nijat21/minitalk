.PHONY: all clean fclean re

NAME1=client
NAME2=server

CC=cc
CFLAGS= -Wall -Wextra -Werror -g

SRCS := client.c server.c
OBJS := $(SRCS:%.c=%.o) 
 
LIBFT_MAKE=make -C Libft
LIBFT_LIB=Libft/libft.a

all: $(NAME2) $(NAME1)

$(NAME2): $(LIBFT_LIB) server.o
	$(CC) $(CFLAGS) server.o $(LIBFT_LIB) -o $(NAME2)

$(NAME1): $(LIBFT_LIB) client.o
	$(CC) $(CFLAGS) client.o $(LIBFT_LIB) -o $(NAME1)

$(LIBFT_LIB):
	$(LIBFT_MAKE) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)
	$(LIBFT_MAKE) clean

fclean: clean
	rm -f $(NAME1) $(NAME2)
	$(LIBFT_MAKE) fclean

re: fclean all