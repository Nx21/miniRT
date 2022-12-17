# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 17:15:03 by nhanafi           #+#    #+#              #
#    Updated: 2022/12/17 17:22:17 by nhanafi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main

GCC = gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

NAME = fractol

INC = include/minirt.h

ODIR = obj

OBJ = $(addprefix $(ODIR)/, $(FILES:=.o))

all: $(NAME)

$(NAME): $(OBJ) 
	$(GCC) $(OBJ) -o $(NAME)

$(ODIR)/%.o: src/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus: all

clean:
	rm -rf $(OBJ)
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all