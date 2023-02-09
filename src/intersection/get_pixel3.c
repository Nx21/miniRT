/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:15:49 by orekabe           #+#    #+#             */
/*   Updated: 2023/02/09 04:16:53 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	pixel_color(t_scene scene, int i, int j)
{
	t_obj	*obj;
	t_point	*tmp;
	t_point	*res;

	res = NULL;
	tmp = NULL;
	obj = scene.obj;
	while (obj)
	{
		tmp = find_intersection(scene.v_cam[i][j], obj);
		if (tmp && (!res || res->distance > tmp->distance))
		{
			free(res);
			res = tmp;
		}
		else
			free(tmp);
		obj = obj->next;
	}
	return (add_light(res, scene, scene.v_cam[i][j]));
}

double	is_intersection_plan(t_coordinates x, t_coordinates v, t_obj *obj)
{
	double	res;
	double	r1;
	double	r2;

	if (!obj)
		return (0);
	x = sub_c(obj->coor, x);
	r1 = dot_prod_c(v, obj->vec);
	r2 = dot_prod_c(x, obj->vec);
	if (r1 < EPSILON || r2 < EPSILON)
		return (0);
	res = r2 / r1;
	if (res < EPSILON)
		return (0);
	return (res);
}

double	is_intersection_square(t_coordinates x, t_coordinates v, t_obj *obj)
{
	double			res;
	double			r1;
	double			r2;
	t_coordinates	tmp;
	t_coordinates	y;

	if (!obj)
		return (0);
	y = x;
	x = sub_c(obj->coor, x);
	r1 = dot_prod_c(v, obj->vec);
	r2 = dot_prod_c(x, obj->vec);
	if (!r1 || !r2)
		return (0);
	res = r2 / r1;
	if (res < EPSILON)
		return (0);
	tmp = sub_c(add_c(prod_c(res, v), y), obj->coor);
	if (fabs(dot_prod_c(tmp, obj->ref.j)) > obj->diameter
		|| fabs(dot_prod_c(tmp, obj->ref.k)) > obj->diameter)
		return (0);
	return (res);
}

double	is_intersection_circle(t_coordinates x, t_coordinates v, t_obj *obj)
{
	double			res;
	double			r1;
	double			r2;
	t_coordinates	tmp;
	t_coordinates	y;

	if (!obj)
		return (0);
	y = x;
	x = sub_c(obj->coor, x);
	r1 = dot_prod_c(v, obj->vec);
	r2 = dot_prod_c(x, obj->vec);
	if (!r1 || !r2)
		return (0);
	res = r2 / r1;
	if (res < EPSILON)
		return (0);
	tmp = sub_c(add_c(prod_c(res, v), y), obj->coor);
	if (dot_prod_c(tmp, tmp) > obj->diameter * obj->diameter)
		return (0);
	return (res);
}
