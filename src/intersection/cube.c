/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:40:06 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/08 19:20:03 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bump_cal(double res, t_coordinates *direction, t_coordinates *normal)
{
	t_coordinates tmp;

	tmp = prod_c((round(res) - res) / 3+ (double)(rand()%110 - 50)/1000, *direction);
	*normal =  add_c(*normal, tmp);
	// *normal = norm_c(*normal);
}

t_point	*intersection_square(t_coordinates v, t_obj *obj)
{
	t_point	*point;
	double tmp = 0;
	double tmp2 = 0;
	double res = 0,res2 = 0;
	t_coordinates x;

	if(!obj || obj->type != 4)
		return NULL;
	point = intersection_plan(v, obj);
	if(!point)
		return NULL;
	x = sub_c(obj->coor, point->point);
	tmp = dot_prod_c(x, obj->ref.j);
	tmp2 = dot_prod_c(x, obj->ref.k);
	if ((fabs(tmp) > obj->diameter) || (fabs(tmp2) > obj->diameter))
		return (free(point), NULL);
	if (!obj->id || !point)
		return point;
	if (obj->id == 2)
	{
		res = dot_prod_c(obj->ref.j, x) *10 / obj->diameter;
		res2 = dot_prod_c(obj->ref.k, x) *10 / obj->diameter;
		if ((int)(round(res2) + round(res)) % 2)
			point->color = obj->color2;
	}
	if(obj->id == 1)
	{
		res = dot_prod_c(obj->ref.j, x) * obj->img.height /obj->diameter;
		res2 = dot_prod_c(obj->ref.k, x) * obj->img.width /obj->diameter;
		int a = (((int)(res) % obj->img.height) + obj->img.height)% obj->img.height;
		int b = (((int)(res2) % obj->img.width) + obj->img.width)% obj->img.width;
		point->color = ft_itocolor(obj->img.addr_int[(a * obj->img.width + b)]);
	}
	// if (obj->id & 4)
	{
		bump_cal(res, &obj->ref.j, &point->normal);
		bump_cal(res2 , &obj->ref.k, &point->normal);
		point->normal = norm_c(point->normal);
	}
	return point;
}