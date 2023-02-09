/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:17:34 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/08 23:23:47 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "get_next_line.h"
# include "utils.h"
# include "mlx.h"

t_obj	*new_obj(int type);
t_obj	*add_front(t_obj *head, t_obj *obj);
void	pars(t_scene *scene, int fd);
void	sphere_pars(char *line, t_scene *scene, int fd);
void	plane_pars(char *line, t_scene *scene, int fd);
void	light_pars(char *line, t_scene *scene, int fd);
void	cylinder_pars(char *line, t_scene *scene, int fd);
void	camera_pars(char *line, t_scene *scene, int fd);
void	ambient_pars(char *line, t_scene *scene, int fd);
void	cube_pars(char *line, t_scene *scene, int fd);
double  dist_sq(t_coordinates a, t_coordinates b);
int		equal_coor(t_coordinates a, t_coordinates b);
int		greater(double a, double b);
int		equal(double a, double b);
double	dist_sq(t_coordinates a, t_coordinates b);
int		equal_coor(t_coordinates a, t_coordinates b);
void    get_v_cam(t_scene *scene);

//vector
t_coordinates	norm_c(t_coordinates v);
t_coordinates	make_coor(double x, double y, double z);
t_coordinates	sub_c(t_coordinates v, t_coordinates u);
t_coordinates	prod_c(double a, t_coordinates u);
t_coordinates	add_c(t_coordinates v, t_coordinates u);
t_coordinates	cross_prod_c(t_coordinates v, t_coordinates u);
double			dot_prod_c(t_coordinates v, t_coordinates u);
t_ref			creat_ref(t_coordinates vec);
t_color 		color_degree(t_color color, double d);
//operation
t_quad_eq    sd_equation(t_quad_eq parm);
//intersection
t_color pixel_color(t_scene scene, int i, int j);
t_point	*intersection_cylindre(t_coordinates v, t_obj *obj);
t_point	*intersection_plan(t_coordinates v ,t_obj *obj);
t_point	*intersection_sphere(t_coordinates v, t_obj *obj);
t_point	*intersection_circle(t_coordinates v, t_obj *obj);
t_point	*intersection_infinit_plan(t_coordinates v ,t_obj *obj);
t_point	*intersection_square(t_coordinates v, t_obj *obj);
void	cube_pars(char *line, t_scene *scene, int fd);
void	bump_cal(double res, t_coordinates *direction, t_coordinates *normal);
// tmp
void printc(t_coordinates c);
t_color add_color(t_color color1, t_color color2);
double magnitude(t_coordinates v);
t_color color_degree(t_color color, double d);
void    get_img(char *file, t_obj *obj);
#endif