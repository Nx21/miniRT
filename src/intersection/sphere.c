/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/02 16:20:10 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point *creat_sphere_point(t_obj *obj, t_coordinates v, double t)
{
    t_point *point;
	static int st = 0;
	double res = 0, res2 = 0, res3, res4;

    point = (t_point *)malloc(sizeof(t_point));
    point->distance = t;
    point->point = prod_c(t, v);
    point->normal = norm_c(sub_c(point->point, obj->coor));
	t_ref ref = creat_ref(point->normal);
	// double teta = (double)(st % 30) * M_PI/360;
	// double alpha = (double)(rand()%180) * M_PI/360;
	st++;
	// point->normal = norm_c(add_c(ref.i, prod_c(sin(teta), ref.j)));

	{
		res = ((point->point.z - obj->coor.z));
		t_coordinates y = prod_c(dot_prod_c(make_coor(0,0,1), point->normal),  make_coor(0,0,1));
		res3 = (obj->coor.x - point->point.x) ;
		res4 = (obj->coor.z - point->point.z) ;
		y = norm_c(sub_c(point->normal, y));
		// y = point->normal;
		res2 = (atan2(y.y, y.x) * 12 / M_PI);
		if ((int)(round(res3) + round(res4)) % 2 == 0)
			point->color = obj->color;
		else
			point->color = obj->color2;
		
		point->normal = norm_c(add_c(point->normal, prod_c(round(res3) - res3 + (double)(rand()%110 - 50)/1000,ref.j)));
		point->normal = norm_c(add_c(point->normal, prod_c(round(res4) - res4 + (double)(rand()%110 - 50)/1000,ref.k)));
			// point->point = prod_c(t - 2 - (round(res3) - res3) - (round(res4) - res4), v);
			// point->point = norm_c(add_c(point->normal, prod_c(res,ref.k)));
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