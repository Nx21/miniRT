/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 04:14:51 by orekabe           #+#    #+#             */
/*   Updated: 2023/02/10 00:27:58 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	find_is_intersection(t_coordinates v, t_obj *obj, t_coordinates x)
{
	if (obj->type == 0)
		return (is_intersection_sphere(x, v, obj));
	else if (obj->type == 1)
		return (is_intersection_plan(x, v, obj));
	else if (obj->type == 2)
		return (is_intersection_cylindre(x, v, obj));
	else if (obj->type == 3)
		return (is_intersection_circle(x, v, obj));
	else if (obj->type == 4)
		return (is_intersection_square(x, v, obj));
	return (0);
}

int	is_intersected(t_scene scene, t_coordinates l, t_coordinates x)
{
	t_obj			*obj;
	double			tmp;
	double			maxdis;
	t_point			*res;
	t_coordinates	v;

	v = sub_c(l, x);
	maxdis = sqrt(dot_prod_c(v, v));
	v = norm_c(v);
	obj = scene.obj;
	res = NULL;
	tmp = 0;
	while (obj)
	{
		tmp = find_is_intersection(v, obj, x);
		if (tmp && tmp < maxdis)
			return (1);
		obj = obj->next;
	}
	return (0);
}

double	is_light(t_point *p, t_light *l, t_coordinates v)
{
	t_coordinates	vprinm;
	t_coordinates	vlight;

	vprinm = norm_c(add_c(v, prod_c(-2 * dot_prod_c(p->normal, v), p->normal)));
	vlight = norm_c(sub_c(l->light_co, p->point));
	return (pow(dot_prod_c(vprinm, vlight), 25));
}

t_point	*find_intersection(t_coordinates v, t_obj *obj)
{
	if (obj->type == 0)
		return (intersection_sphere(v, obj));
	else if (obj->type == 1)
		return (intersection_infinit_plan(v, obj));
	else if (obj->type == 2)
		return (intersection_cylindre(v, obj));
	else if (obj->type == 3)
		return (intersection_circle(v, obj));
	else if (obj->type == 4)
		return (intersection_square(v, obj));
	return (NULL);
}

t_color	add_light(t_point *res, t_scene scene, t_coordinates v)
{
	t_color	color;
	t_light	*l;

	l = scene.light;
	color = ft_itocolor(0);
	while (l)
	{
		if (res && !is_intersected(scene, l->light_co, res->point))
		{
			color = add_color(color, (add_color(prod_color(l->light_color,
								color_degree(res->color, l->light_b
									* fabs(dot_prod_c(norm_c(sub_c(l->light_co,
													res->point)),
											res->normal)))),
							color_degree(l->light_color, l->light_b
								* is_light(res, l, v)))));
		}
		l = l->next;
	}
	if (res)
	{
		color = add_color(color, color_degree(res->color, scene.ratio));
		return (free(res), color);
	}
	return (ft_itocolor(0));
}
