/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:21:29 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:49:53 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	*creat_point_cylindre(t_coordinates p, t_coordinates c, t_coordinates v)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		err();
	point->point = p;
	point->normal = norm_c(sub_c(sub_c(p, c), v));
	return (point);
}

t_point	*texture_cylindre(t_point *point, t_obj *obj)
{
	double			res;
	double			res2;
	t_coordinates	x;
	int				a;
	int				b;

	res = ((fabs(dot_prod_c(sub_c(point->point, obj->coor), obj->vec))
				/ obj->height) * obj->img.height / 2);
	x = prod_c(dot_prod_c(obj->ref.i, point->normal), obj->ref.i);
	x = norm_c(sub_c(point->normal, x));
	res2 = (1 - atan2(dot_prod_c(obj->ref.j, x),
				dot_prod_c(obj->ref.k, x)) / M_PI) * obj->img.width;
	a = (((int)(res) % obj->img.height) + obj->img.height) % obj->img.height;
	b = (((int)(res2) % obj->img.width) + obj->img.width) % obj->img.width;
	point->color = ft_itocolor(obj->img.addr_int[(a * obj->img.width + b)]);
	if (obj->img.sqsize)
	{
		bump_cal(res * obj->img.sqsize / obj->img.height,
			&obj->ref.j, &point->normal);
		bump_cal(res2 * obj->img.sqsize / obj->img.width,
			&obj->ref.k, &point->normal);
		point->normal = norm_c(point->normal);
	}
	return (point);
}

t_point	*checkerboard_cylindre(t_point *point, t_obj *obj)
{
	double			res;
	double			res2;
	t_coordinates	x;

	res = ((fabs(dot_prod_c(sub_c(point->point, obj->coor), obj->vec))));
	x = sub_c(obj->coor, point->point);
	res2 = (1 + atan2(dot_prod_c(obj->ref.k, x),
				dot_prod_c(obj->ref.j, x)) / M_PI) * obj->diameter * 5;
	if ((int)(round(res2) + round(res)) % 2)
		point->color = obj->color2;
	return (point);
}

t_point	*get_point_cylindre(t_quad_eq parm, t_obj *obj, t_coordinates v)
{
	double	m;
	t_point	*point;

	m = dot_prod_c(v, obj->vec) * parm.r1 - dot_prod_c(obj->coor, obj->vec);
	if (m < 0 || m > obj->height)
		return (NULL);
	point = creat_point_cylindre(prod_c(parm.r1, v),
			obj->coor, prod_c(m, obj->vec));
	point->color = obj->color;
	point->distance = parm.r1;
	if (!obj->id)
		return (point);
	if (obj->id == 1)
		return (texture_cylindre(point, obj));
	return (checkerboard_cylindre(point, obj));
}

t_point	*intersection_cylindre(t_coordinates v, t_obj *obj)
{
	t_quad_eq		parm;

	if (!obj || obj->type != 2)
		return (NULL);
	parm.a = dot_prod_c(v, v) - pow(dot_prod_c(v, obj->vec), 2);
	parm.b = -2 * (dot_prod_c(v, obj->coor) - dot_prod_c(v, obj->vec)
			* dot_prod_c(obj->coor, obj->vec));
	parm.c = dot_prod_c(obj->coor, obj->coor)
		- pow(dot_prod_c(obj->coor, obj->vec), 2) - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta < EPSILON)
		return (NULL);
	return (get_point_cylindre(parm, obj, v));
}
