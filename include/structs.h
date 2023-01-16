/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:57:50 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/14 14:57:38 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define EPSILON 1e-6
# define WIDTH 1080
# define HEIGHT	720
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


typedef struct s_scene
{
	int				ambientcolor;
	double			ratio;
	t_coordinates	**cam;
	t_coordinates	cam_co;
	t_coordinates	cam_vec_x;
	t_coordinates	cam_vec_y;
	t_coordinates	cam_vec_z;
	double			fov;
	t_coordinates	vvp;
	t_coordinates	light_co;
	double			light_b;
	int				light_color;
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

typedef struct s_mat
{
	size_t		raw;
	size_t		col;
	double		**l;
} t_mat;
double  dist_sqv(t_coordinates v);
t_coordinates prod_c(double a, t_coordinates u);

#endif