NAMECLT = client
NAMESRV = server

PATH_LIBFT = libft
LIBFT = $(PATH_LIBFT)/libft.a

PATH_SRCS = srcs

SRC_CLIENT = client.c

SRC_SRV = server.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

OBJ_SRV = $(SRC_SRV:.c=.o)

CC = cc

CFLAGS = -g3 #-Wall -Wextra -Werror #-fsanitize=address,undefined

RM = rm -f

all: $(LIBFT) $(NAMECLT) $(NAMESRV)

$(NAMECLT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(NAMECLT) $(OBJ_CLIENT) $(LIBFT)

$(NAMESRV): $(OBJ_SRV)
	$(CC) $(CFLAGS) -o $(NAMESRV) $(OBJ_SRV) $(LIBFT)

.c.o:
	$(CC) $(CFLAGS) -I $(PATH_LIBFT) -c $< -o $(<:.c=.o)

$(LIBFT):
	$(MAKE) -C $(PATH_LIBFT)

clean:
	$(MAKE) -C $(PATH_LIBFT) clean
	$(RM) $(OBJ_SRV) $(OBJ_CLIENT)

fclean: clean
	$(MAKE) -C $(PATH_LIBFT) fclean
	$(RM) $(NAMECLT) $(NAMESRV)

re: fclean all

.PHONY: all clean fclean re
