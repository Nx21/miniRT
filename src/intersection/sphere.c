/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/30 05:52:49 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point *creat_sphere_point(t_obj *obj, t_coordinates v, double t)
{
    t_point *point;
	int res = 0, res2 = 0;

    point = (t_point *)malloc(sizeof(t_point));
    point->distance = t;
    point->point = prod_c(t, v);
    point->normal = norm_c(sub_c(point->point, obj->coor));
	{
		t_coordinates x = prod_c(dot_prod_c(make_coor(0,1,0), point->normal),  make_coor(0,1,0));
		x = norm_c(sub_c(point->normal, x));
		res = (acos((dot_prod_c(x, make_coor(1,0,0)))) * 5);
		t_coordinates y = prod_c(dot_prod_c(make_coor(0,0,1), point->normal),  make_coor(0,0,1));
		y = norm_c(sub_c(point->normal, y));
		res2 = (acos(dot_prod_c(y, make_coor(1,0,0))) * 5);
		if ((res + res2) % 2)
			point->color = obj->color;
		else
			point->color = ft_itocolor(0xffffff);
	}
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