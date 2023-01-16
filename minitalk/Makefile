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

CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address,undefined

RM = rm -f

all: $(LIBFT) $(NAMECLT) $(NAMESRV)

$(NAMECLT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -g3 -o $(NAMECLT) $(OBJ_CLIENT) $(LIBFT)

$(NAMESRV): $(OBJ_SRV)
	$(CC) $(CFLAGS) -o $(NAMESRV) $(OBJ_SRV) $(LIBFT)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(PATH_LIBFT)

$(LIBFT):
	$(MAKE) -C $(PATH_LIBFT)

clean:
	$(MAKE) -C $(PATH_LIBFT) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(PATH_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
