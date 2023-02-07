/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:38:22 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/07 14:32:21 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point *creat_plane_point(t_obj *obj, t_coordinates v, double t)
{
    t_point *point;

    point = (t_point *)malloc(sizeof(t_point));
    point->distance = t;
    point->point = prod_c(t, v);
    point->normal = obj->vec;
    point->color = obj->color;
	return point;
}

t_point	*intersection_plan(t_coordinates v, t_obj *obj)
{
	double res,r1,r2;

	if(!obj)
		return NULL;
	r1 = dot_prod_c(v, obj->vec);
	r2 = dot_prod_c(obj->coor,obj->vec);
	if (!r1 && !r2)
		return creat_plane_point(obj, v, 0);
	if (!r1)
		return NULL;
	res = r2/r1;
	if (res < EPSILON)
		return NULL;
	return (creat_plane_point(obj, v, res));
}

t_point	*intersection_infinit_plan(t_coordinates v ,t_obj *obj)
{
	t_point *point;
	double res,res2;
	t_ref ref;
	t_coordinates x;

	point = intersection_plan(v, obj);
	if (!obj->id || !point)
		return point;
	if (obj->id)
	{
		x = sub_c(obj->coor, point->point);
		ref = creat_ref(point->normal);
		res = (((dot_prod_c(x, ref.j))));
		res2 = ((dot_prod_c(x, ref.k)));
	}
	if (obj->id == 2 && (int)(res + res2)%2)
		point->color = obj->color2;
	if(obj->id == 1)
	{
		int a = (((int)(res * 10) % obj->img.height) + obj->img.height)% obj->img.height;
		int b = (((int)(res2 * 10) % obj->img.width) + obj->img.width)% obj->img.width;
		point->color = ft_itocolor(obj->img.addr_int[(a * obj->img.width + b)]);
		point->normal = norm_c(add_c(point->normal, prod_c(-(round(res ) - res) / 3+ (double)(rand()%110 - 50)/1000 ,ref.j)));
		point->normal = norm_c(add_c(point->normal, prod_c(-(round(res2 ) - res2 ) / 3+ (double)(rand()%110 - 50)/1000,ref.k)));
	}
	return point;
}