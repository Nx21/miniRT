/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/25 13:13:36 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point *creat_sphere_point(t_obj *obj, t_coordinates v, double t)
{
    t_point *point;

    point = (t_point *)malloc(sizeof(t_point));
    point->distance = t;
    point->point = prod_c(t, v);
    point->normal = norm_c(sub_c(point->point, obj->coor));
	// {
	// 	t_coordinates z = cross_prod_c(point->normal, make_coor(1,1,1));
	// 	t_coordinates y = cross_prod_c(z,point->normal);
	// 	double angle1 = M_PI* (rand() % 11 - 5)/1000;
	// 	double angle2 = M_PI* (rand() % 11 - 5)/1000;
	// 	point->normal = add_c(prod_c(cos(angle1), point->normal), prod_c(sin(angle1), y));
	// 	point->normal = add_c(prod_c(cos(angle2), point->normal), prod_c(sin(angle2), z));
	// }
    point->color = obj->color;
    return point;
}


t_point	*intersection_sphere(t_coordinates v, t_obj *obj)
{
	t_quad_eq   parm;

	if(!obj || obj->type != 0)
		return NULL;
	parm.a = dot_prod_c(v,v);
	parm.b = -2 * dot_prod_c(v, obj->coor);
	parm.c = dot_prod_c(obj->coor, obj->coor)  - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta < EPSILON)
		return (NULL);
	return (creat_sphere_point(obj, v, parm.r1));
}