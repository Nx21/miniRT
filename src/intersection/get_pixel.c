/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:54:46 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 04:16:20 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_degree(t_color color, double d)
{
	t_color	res;

	res.r = (color.r & 0xff) * d;
	if (res.r > 255)
		res.r = 255;
	if (res.r < 1)
		res.r = 0;
	res.g = (color.g & 0xff) * d;
	if (res.g > 255)
		res.g = 255;
	if (res.g < 1)
		res.g = 0;
	res.b = (color.b & 0xff) * d;
	if (res.b < 1)
		res.b = 0;
	if (res.b >= 255)
		res.b = 255;
	return (res);
}

t_color	add_color(t_color color1, t_color color2)
{
	t_color	res;

	res.r = ((color1.r & 0xff) + (color2.r & 0xff));
	if (res.r > 255)
		res.r = 255;
	if (res.r < 1)
		res.r = 0;
	res.g = ((color1.g & 0xff) + (color2.g & 0xff));
	if (res.g > 255)
		res.g = 255;
	if (res.g < 1)
		res.g = 0;
	res.b = ((color1.b & 0xff) + (color2.b & 0xff));
	if (res.b < 1)
		res.b = 0;
	if (res.b >= 255)
		res.b = 255;
	return (res);
}

t_color	prod_color(t_color color1, t_color color2)
{
	t_color	res;

	res.r = ((color1.r & 0xff) * (color2.r & 0xff)) / 256;
	if (res.r > 255)
		res.r = 255;
	if (res.r < 1)
		res.r = 0;
	res.g = ((color1.g & 0xff) * (color2.g & 0xff)) / 256;
	if (res.g > 255)
		res.g = 255;
	if (res.g < 1)
		res.g = 0;
	res.b = ((color1.b & 0xff) * (color2.b & 0xff)) / 256;
	if (res.b < 1)
		res.b = 0;
	if (res.b >= 255)
		res.b = 255;
	return (res);
}

double	is_intersection_sphere(t_coordinates x, t_coordinates v, t_obj *obj)
{
	t_quad_eq	parm;

	x = sub_c(obj->coor, x);
	if (!obj || obj->type != 0)
		return (0);
	parm.a = dot_prod_c(v, v);
	parm.b = -2 * dot_prod_c(v, x);
	parm.c = dot_prod_c(x, x) - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta <= EPSILON || (parm.r1 <= EPSILON && parm.r2 <= EPSILON))
		return (0);
	if (parm.r1 >= -EPSILON)
		return (parm.r1);
	if (parm.r2 >= -EPSILON)
		return (parm.r1);
	return (0);
}

double	is_intersection_cylindre(t_coordinates x, t_coordinates v, t_obj *obj)
{
	t_quad_eq	parm;
	double		m;

	if (!obj || obj->type != 2)
		return (0);
	x = sub_c(obj->coor, x);
	parm.a = dot_prod_c(v, v) - pow(dot_prod_c(v, obj->vec), 2);
	parm.b = -2 * (dot_prod_c(v, x) - dot_prod_c(v, obj->vec)
			* dot_prod_c(x, obj->vec));
	parm.c = dot_prod_c(x, x) - pow(dot_prod_c(x, obj->vec), 2)
		- pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta < EPSILON || (parm.r1 <= EPSILON && parm.r2 <= EPSILON))
		return (0);
	m = dot_prod_c(v, obj->vec) * parm.r1 - dot_prod_c(x, obj->vec);
	if (m >= 0 && m <= obj->height)
		return (parm.r1);
	return (0);
}
