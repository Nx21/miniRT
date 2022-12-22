# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 17:15:03 by nhanafi           #+#    #+#              #
#    Updated: 2022/12/22 01:46:51 by nhanafi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main

GCC = gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

NAME = minirt

INC = include

HEADER = include/minirt.h

ODIR = obj

OBJ = $(addprefix $(ODIR)/, $(FILES:=.o))

all: $(NAME)

$(NAME): $(OBJ) 
	$(GCC) $(OBJ) -o $(NAME)

$(ODIR)/%.o: src/%.c $(HEADER)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

bonus: all

clean:
	rm -rf $(OBJ)
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all