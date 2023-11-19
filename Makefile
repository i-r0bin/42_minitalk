# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rilliano <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 13:45:47 by rilliano          #+#    #+#              #
#    Updated: 2023/09/01 13:45:51 by rilliano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = src/
O = obj/
I = ./
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a

SRC_S = $Sserver.c
SRC_C =	$Sclient.c
BSRC_S = $Sserver_bonus.c
BSRC_C = $Sclient_bonus.c

OBJ_S = $(SRC_S:$S%.c=$O%.o)
OBJ_C = $(SRC_C:$S%.c=$O%.o)
BOBJ_S = $(BSRC_S:$S%.c=$O%.o)
BOBJ_C = $(BSRC_C:$S%.c=$O%.o)

NAME = client
NAME_S = server
NAME_BC = client_bonus
NAME_BS = server_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

all:	$(NAME) $(NAME_S)

$(LIBFT):
	make -C $(LIBFT_PATH) all

$O:
	mkdir -p $@

$(OBJ_S): | $O
$(OBJ_C): | $O
$(BOBJ_S): | $O
$(BOBJ_C): | $O

$O%.o: $S%.c
	$(CC) $(CFLAGS) -I$I -c $^ -o $@

$(NAME): $(OBJ_C) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@ -L $(LIBFT_PATH) -lft

$(NAME_S): $(OBJ_S) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@ -L $(LIBFT_PATH) -lft

bonus:	$(NAME_BC) $(NAME_BS)

$(NAME_BC): $(BOBJ_C) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@ -L $(LIBFT_PATH) -lft

$(NAME_BS): $(BOBJ_S) $(LIBFT)
	$(CC) $(CFLAGS) $< -o $@ -L $(LIBFT_PATH) -lft

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) -r $O

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME) $(NAME_S) $(NAME_BC) $(NAME_BS)

re:	fclean all

.PHONY:	all bonus clean fclean re libft
