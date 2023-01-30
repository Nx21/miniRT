# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 17:15:03 by nhanafi           #+#    #+#              #
#    Updated: 2023/01/30 05:57:11 by nhanafi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main add_front utils/ft_atoi utils/ft_isalnum utils/ft_putstr_fd utils/ft_strdup\
	utils/ft_strstr utils/instr utils/ft_calloc utils/ft_itoa utils/ft_memset utils/ft_split utils/ft_strcmp \
	utils/ft_strlen utils/ft_substr utils/end_with utils/ft_strtrim utils/ft_atof utils/ft_strrchr\
	utils/ft_atoc utils/ft_count utils/ft_lstsize utils/ft_atocolor utils/ft_fswap\
	get_next_line/get_next_line get_next_line/get_next_line_utils\
	pars/ambient pars/camera pars/cylindre pars/light pars/pars pars/plane pars/sphere pars/get_v_cam\
	operation/equal operation/vector operation/vector_operation operation/sd_equation\
	intersection/sphere intersection/plane intersection/cylindre intersection/get_pixel intersection/circle
	

CC = cc -Wall -Wextra -Werror

NAME = minirt

INC = include

HEADER = include/minirt.h include/utils.h include/get_next_line.h include/structs.h

ODIR = obj

OBJ = $(addprefix $(ODIR)/, $(FILES:=.o))

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(OBJ) -o $(NAME)  -lmlx -framework OpenGL -framework AppKit

$(ODIR)/%.o: src/%.c $(HEADER)
	mkdir -p $(@D)
	$(CC) -I$(INC) -c $< -o $@

bonus: all

clean:
	rm -rf $(ODIR) 
	
fclean: clean
	rm -rf $(NAME)
	
re: fclean all