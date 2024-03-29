/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:57:50 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 05:23:12 by orekabe          ###   ########.fr       */
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
# include <pthread.h>

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
}				t_coordinates;

typedef struct s_ref
{
	t_coordinates	i;
	t_coordinates	j;
	t_coordinates	k;
}				t_ref;

typedef struct s_color
{
	int	tr;
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		*addr_int;
	int		bits_per_pixel;
	void	*mlx;
	void	*mlx_win;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	double	sqsize;
}				t_data;

typedef struct s_obj
{
	int				id;
	int				type;
	t_coordinates	coor;
	t_color			color;
	t_color			color2;
	t_coordinates	vec;
	double			diameter;
	double			height;
	t_data			img;
	t_ref			ref;
	struct s_obj	*next;
}				t_obj;

typedef struct s_light
{
	t_coordinates	light_co;
	double			light_b;
	t_color			light_color;
	struct s_light	*next;
}				t_light;

typedef struct s_scene
{
	t_color			ambientcolor;
	double			ratio;
	t_coordinates	**v_cam;
	t_coordinates	cam_co;
	t_coordinates	cam_vec_x;
	double			fov;
	t_light			*light;
	t_obj			*obj;
	t_data			img;
	int				rep;
}				t_scene;

typedef struct s_point
{
	double			distance;
	t_coordinates	point;
	t_coordinates	normal;	
	t_color			color;
}				t_point;

typedef struct s_quad_eq
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	r1;
	double	r2;
}	t_quad_eq;

typedef struct s_thread
{
	t_scene		*scene;
	pthread_t	thread;
	int			id;
	int			start;
	int			end;
}				t_thread;

#endif