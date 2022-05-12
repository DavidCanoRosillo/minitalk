NAME_SERVER = server
NAME_CLIENT = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
SRC_SERVER = server.c ft_putnbr_fd.c
SRC_CLIENT = client.c ft_atoi.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER)  

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT)  

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all
