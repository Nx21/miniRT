/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:40:06 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/14 18:48:29 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bump_cal(double res, t_coordinates *direction, t_coordinates *normal)
{
	t_coordinates	tmp;

	tmp = prod_c(res, *direction);
	*normal = add_c(*normal, tmp);
	*normal = norm_c(*normal);
}

t_point	*texture_square(t_point *point, t_obj *obj)
{
	double			res;
	double			res2;
	t_coordinates	x;
	int				a;
	int				b;

	res = 0;
	res2 = 0;
	x = sub_c(obj->coor, point->point);
	res = (1 + dot_prod_c(obj->ref.k, x) / obj->diameter) * obj->img.height / 2;
	res2 = (1 + dot_prod_c(obj->ref.j, x) / obj->diameter) * obj->img.width / 2;
	a = (((int)(res) % obj->img.height) + obj->img.height) % obj->img.height;
	b = (((int)(res2) % obj->img.width) + obj->img.width) % obj->img.width;
	point->color = ft_itocolor(obj->img.addr_int[(a * obj->img.width + b)]);
	if (obj->img.sqsize)
	{
		bump_cal(-res * obj->img.sqsize / obj->img.height,
			&obj->ref.k, &point->normal);
		bump_cal(-res2 * obj->img.sqsize / obj->img.width,
			&obj->ref.j, &point->normal);
		point->normal = norm_c(point->normal);
	}
	return (point);
}

t_point	*checkerboard_square(t_point *point, t_obj *obj)
{
	double			res;
	double			res2;
	t_coordinates	x;

	res = 0;
	res2 = 0;
	x = sub_c(obj->coor, point->point);
	res = dot_prod_c(obj->ref.j, x) * 10 / obj->diameter;
	res2 = dot_prod_c(obj->ref.k, x) * 10 / obj->diameter;
	if ((int)(round(res2) + round(res)) % 2)
		point->color = obj->color2;
	return (point);
}

t_point	*intersection_square(t_coordinates v, t_obj *obj)
{
	t_point			*point;
	double			tmp;
	double			tmp2;
	t_coordinates	x;

	tmp = 0;
	tmp2 = 0;
	if (!obj || obj->type != 4)
		return (NULL);
	point = intersection_plan(v, obj);
	if (!point)
		return (NULL);
	x = sub_c(obj->coor, point->point);
	tmp = dot_prod_c(x, obj->ref.j);
	tmp2 = dot_prod_c(x, obj->ref.k);
	if ((fabs(tmp) > obj->diameter) || (fabs(tmp2) > obj->diameter))
		return (free(point), NULL);
	if (!obj->id || !point)
		return (point);
	if (obj->id == 2)
		return (checkerboard_square(point, obj));
	if (obj->id == 1)
		return (texture_square(point, obj));
	return (point);
}
