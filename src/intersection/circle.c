/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/08 23:34:47 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_point	*texture_circle(t_point *point, t_obj *obj)
{
	double res = 0,res2 = 0;
	t_coordinates x;
	int				a;
	int				b;

	x = sub_c(obj->coor, point->point);
	res = (1 + atan(dot_prod_c(obj->ref.j, x)/ dot_prod_c(obj->ref.k, x))/M_PI) *obj->diameter;
	res2 = sqrt((dot_prod_c(x, x)));
	a = (((int)(res * 10) % obj->img.height) + obj->img.height)% obj->img.height;
	b = (((int)(res2 * 10) % obj->img.width) + obj->img.width)% obj->img.width;
	point->color = ft_itocolor(obj->img.addr_int[(a * obj->img.width + b)]);
	if (obj->img.sqsize)
	{
		bump_cal(res * obj->img.sqsize / obj->img.height, &obj->ref.j, &point->normal);
		bump_cal(res2 * obj->img.sqsize / obj->img.width , &obj->ref.k, &point->normal);
		point->normal = norm_c(point->normal);
	}
	return point;
}

t_point	*checkerboard_circle(t_point *point, t_obj *obj)
{
	double res = 0,res2 = 0;
	t_coordinates x;

	x = sub_c(obj->coor, point->point);
	res = (1 + atan(dot_prod_c(obj->ref.j, x)/ dot_prod_c(obj->ref.k, x))/M_PI) *obj->diameter;
	res2 = sqrt((dot_prod_c(x, x)));
	if ((int)(round(res2) + round(res)) % 2)
		point->color = obj->color2;
	return point;
}


t_point	*intersection_circle(t_coordinates v, t_obj *obj)
{
	t_point	*point;
	t_coordinates tmp;
	t_coordinates x;

	if(!obj || obj->type != 3)
		return NULL;
	point = intersection_plan(v, obj);
	if(!point)
		return NULL;
	x = sub_c(obj->coor, point->point);
	tmp = sub_c(point->point, obj->coor);
	if (dot_prod_c(tmp, tmp) > (obj->diameter * obj->diameter))
		return (free(point), NULL);
	if (!obj->id || !point)
		return point;
	if (obj->id == 2)
		checkerboard_circle(point, obj);
	if(obj->id == 1)
		return texture_circle(point, obj);
	return point;
}