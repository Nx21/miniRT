/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:17:34 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/26 02:51:05 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
# include "get_next_line.h"
# include "utils.h"
# include "mlx.h"


typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_obj
{
	int				type;
	t_coordinates	coor;
	int				color;
	t_coordinates	vec;
	double			diameter;
	double			height;
	struct s_obj	*next;
}	t_obj;


typedef struct s_scene
{
	int				ambientcolor;
	double			ratio;
	t_coordinates	cam_co;
	t_coordinates	cam_vec;
	int				fov;
	t_coordinates	light_co;
	double			light_b;
	int				light_color;
	t_obj			*obj;
}	t_scene;


#endif