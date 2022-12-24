# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 17:15:03 by nhanafi           #+#    #+#              #
#    Updated: 2022/12/24 21:49:30 by nhanafi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main utils/ft_atoi utils/ft_isalnum utils/ft_join utils/ft_putstr_fd utils/ft_strcat utils/ft_strdup\
	utils/ft_strstr utils/instr utils/ft_calloc utils/ft_itoa utils/ft_memset utils/ft_split utils/ft_strcmp \
	utils/ft_strlen utils/ft_substr\
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
	

GCC = gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

NAME = minirt

INC = include

HEADER = include/minirt.h include/utils.h include/get_next_line.h

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