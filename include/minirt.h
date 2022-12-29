/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:17:34 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/29 05:10:11 by nhanafi          ###   ########.fr       */
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
	t_coordinates	cam_co;
	t_coordinates	cam_vec;
	double				fov;
	t_coordinates	light_co;
	double			light_b;
	int				light_color;
	t_obj			*obj;
}	t_scene;

t_obj	*new_obj(int type);
t_obj	*add_back(t_obj *head, t_obj *obj);
void	pars(t_scene *scene, int fd);
void	sphere_pars(char *line, t_scene *scene, int fd);
void	plane_pars(char *line, t_scene *scene, int fd);
void	light_pars(char *line, t_scene *scene, int fd);
void	cylinder_pars(char *line, t_scene *scene, int fd);
void	camera_pars(char *line, t_scene *scene, int fd);
void	ambient_pars(char *line, t_scene *scene, int fd);
// tmp
void printc(t_coordinates c);
#endif