/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:38:22 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/30 04:22:26 by nhanafi          ###   ########.fr       */
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

t_point	*intersection_plan(t_coordinates v ,t_obj *obj)
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
	if (res < 0)
		return NULL;
	return (creat_plane_point(obj, v, res));
}