.PHONY: all clean fclean re

CLIENT=client
SERVER=server

CLIENT_BONUS=client_bonus
SERVER_BONUS=server_bonus

CC=cc
CFLAGS= -Wall -Wextra -Werror -g

SRCS := client.c server.c client_bonus.c server_bonus.c
OBJS := $(SRCS:%.c=%.o) 
 
LIBFT_MAKE=make -C Libft
LIBFT_LIB=Libft/libft.a


all: $(SERVER) $(CLIENT) bonus

$(SERVER): $(LIBFT_LIB) server.o
	$(CC) $(CFLAGS) server.o $(LIBFT_LIB) -o $(SERVER)

$(CLIENT): $(LIBFT_LIB) client.o
	$(CC) $(CFLAGS) client.o $(LIBFT_LIB) -o $(CLIENT)



bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(LIBFT_LIB) server_bonus.o
	$(CC) $(CFLAGS) server_bonus.o $(LIBFT_LIB) -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(LIBFT_LIB) client_bonus.o
	$(CC) $(CFLAGS) client_bonus.o $(LIBFT_LIB) -o $(CLIENT_BONUS)



$(LIBFT_LIB):
	$(LIBFT_MAKE) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)
	$(LIBFT_MAKE) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)
	$(LIBFT_MAKE) fclean

re: fclean all