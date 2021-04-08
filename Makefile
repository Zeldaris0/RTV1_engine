# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/11 10:39:21 by abenani           #+#    #+#              #
#    Updated: 2021/02/23 14:55:47 by moel-aza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MD
SDLSRC = SDL2-2.0.12.tar.gz
SDL = SDL2-2.0.12
SDLB = $(SDL)/build
C_SDL = `$(SDLB)/sdl2-config --cflags --libs`
LIBFTD = libft
SRC_D = srcs



SRC_F = main.c sdltools.c vecs.c rendertools.c parser1.c parsercamlight.c shapes.c colors.c parser_obj.c nrms.c nodes.c vecs2.c shapesntools.c
SRC = $(addprefix srcs/, $(SRC_F))
OBJ = $(SRC:.c=.o)
DP = $(OBJ:.o=.d)
LIBFT = libft/libft.a


all: $(NAME)

$(NAME):$(SDL) $(OBJ)
		 @$(MAKE) -C $(LIBFTD)
		 $(CC) $(OBJ) $(LIBFT) $(C_SDL) -o $@ -lm

$(SDL):
		tar -xf $(SDLSRC) && mkdir $(SDLB)
		cd $(SDLB) && ../configure --prefix=$(shell pwd)/$(SDLB)
		$(MAKE) -C $(SDLB)
		$(MAKE) -C $(SDLB) install

$(SRC_D)/%.o: $(SRC_D)%.c
		$(CC) $(CFLAGS) -c $< -o $@
clean:
		rm -f $(OBJ)
		rm -f $(DP)
		@$(MAKE) -C $(LIBFTD) clean	
fclean: clean
		@$(MAKE) -C $(LIBFTD) fclean
		rm -f $(NAME)
		rm -rf $(SDL)
re: fclean all
-include $(DP)