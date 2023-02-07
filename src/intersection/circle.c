/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/07 16:00:56 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_point	*intersection_circle(t_coordinates v, t_obj *obj)
{
	t_point	*point;
	t_coordinates tmp;
	double res = 0,res2 = 0;
	t_ref ref;
	t_coordinates x;

	if(!obj || obj->type != 3)
		return NULL;
	point = intersection_plan(v, obj);
	if(!point)
		return NULL;
	ref = creat_ref(point->normal);
	x = sub_c(obj->coor, point->point);
	tmp = sub_c(point->point, obj->coor);
	if (dot_prod_c(tmp, tmp) > (obj->diameter * obj->diameter))
		return (free(point), NULL);
	if (!obj->id || !point)
		return point;
	if (obj->id == 2)
	{
		res = (1 + atan(dot_prod_c(ref.j, x)/ dot_prod_c(ref.k, x))/M_PI) *obj->diameter;
		res2 = sqrt((dot_prod_c(x, x)));
		if ((int)(round(res2) + round(res)) % 2)
			point->color = obj->color2;
	}
	if(obj->id == 1)
	{
		res = (1 + atan(dot_prod_c(ref.j, x)/ dot_prod_c(ref.k, x))/M_PI) *obj->diameter;
		res2 = sqrt((dot_prod_c(x, x)));
		int a = (((int)(res * 10) % obj->img.height) + obj->img.height)% obj->img.height;
		int b = (((int)(res2 * 10) % obj->img.width) + obj->img.width)% obj->img.width;
		point->color = ft_itocolor(obj->img.addr_int[(a * obj->img.width + b)]);
	}
	// if (obj->id & 4)
	{
		point->normal = norm_c(add_c(point->normal, prod_c(-(round(res ) - res) / 3+ (double)(rand()%110 - 50)/1000 ,ref.j)));
		point->normal = norm_c(add_c(point->normal, prod_c(-(round(res2 ) - res2 ) / 3+ (double)(rand()%110 - 50)/1000,ref.k)));
	}
	return point;
}