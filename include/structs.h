/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:57:50 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/25 12:54:15 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define EPSILON 1e-6
# define WIDTH 720
# define HEIGHT	720

# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef	struct s_coordinates
{
	double	x;
	double	y;
	double	z;
}	t_coordinates;

typedef struct s_obj
{
	int				id;
	int				type;
	t_coordinates	coor;
	int				color;
	t_coordinates	vec;
	double			diameter;
	double			height;
	struct s_obj	*next;
}	t_obj;

typedef struct s_light
{
	t_coordinates	light_co;
	double			light_b;
	int				light_color;
	struct s_light	*next;
} t_light;


typedef struct s_scene
{
	int				ambientcolor;
	double			ratio;
	t_coordinates	**v_cam;
	t_coordinates	cam_co;
	t_coordinates	cam_vec_x;
	t_coordinates	cam_vec_y;
	t_coordinates	cam_vec_z;
	double			fov;
	t_light			*light;
	t_obj			*obj;
}	t_scene;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	scene;
}				t_data;

typedef struct s_point
{
	double			distance;
	t_coordinates	point;
	t_coordinates	normal;	
	int				color;
} t_point;

typedef struct s_quad_eq
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	r1;
	double	r2;
}	t_quad_eq;

#endif