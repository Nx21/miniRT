/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/05 19:14:55 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point *creat_sphere_point(t_obj *obj, t_coordinates v, double t)
{
    t_point *point;
	double res = 0, res2 = 0;
	double res3 = 0, res4 = 0;

    point = (t_point *)malloc(sizeof(t_point));
    point->distance = t;
    point->point = prod_c(t, v);
    point->normal = norm_c(sub_c(point->point, obj->coor));
	point->color = obj->color;
	t_ref ref = creat_ref(point->normal);
	t_coordinates y = prod_c(dot_prod_c(make_coor(0,0,1), point->normal),  make_coor(0,0,1));
	y = norm_c(sub_c(point->normal, y));
	if (obj->id)
	{
		res = (((point->point.z - obj->coor.z)/(obj->diameter)) + 1) * obj->img.height/2;
		res2 =  (1 + (atan2(y.x, y.y)/ (M_PI))) * obj->img.width/2;
		point->color = ft_itocolor(obj->img.addr_int[(int)(res) * obj->img.width + (int)(res2)]);
		// if ((int)(round(res) + round(res2)) % 2 == 0)
		// 	point->color = ft_itocolor( 0xffff);
		// else
		res3 = (obj->coor.y - point->point.y);
		res4 = -(obj->coor.z - point->point.z);
		point->normal = norm_c(add_c(point->normal, prod_c((round(res3) - res3) + (double)(rand()%310 - 150)/1000 ,ref.j)));
		point->normal = norm_c(add_c(point->normal, prod_c((round(res4) - res4)+(double)(rand()%310 - 150)/1000,ref.k)));
		
			point->point = prod_c(t -  fabs(round(res3) - res3) - fabs(round(res4) - res4), v);
		// 	point->point = norm_c(add_c(point->normal, prod_c(res,ref.k)));
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