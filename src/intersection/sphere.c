/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/14 19:07:39 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	*texture_sphere(t_point *point, t_obj *obj)
{
	double			res;
	double			res2;
	double			y1;
	double			y2;
	double			r1;
	double			r2;
	// static		int	max = 0;
	t_coordinates	x;

	res = 0;
	res2 = 0;
	x = prod_c(dot_prod_c(make_coor(0, 0, 1),
				point->normal), make_coor(0, 0, 1));
	x = norm_c(sub_c(point->normal, x));
	res = (((point->point.z - obj->coor.z) / (obj->diameter)) + 1)
		* obj->img.height / 2;
	res2 = (1 - (atan2(x.x, x.y) / (M_PI))) * obj->img.width / 2;
	point->color = ft_itocolor(obj->img.addr_int[(int)res
			* obj->img.width + (int)res2]);
	y1 = obj->bump.addr_int[((int)(res - 1 + obj->img.height) % obj->img.height) * obj->img.width + (int)res2];
	y2 = obj->bump.addr_int[((int)(res + 1 + obj->img.height) % obj->img.height) * obj->img.width + (int)res2];
	r1 = -(y2 - y1)/0x0300000;
	// if (fabs(y1) > max)
	// 	max = fabs(y1);
	// if (fabs(y2) > max)
	// 	max = fabs(y2);
	
	y1 = obj->bump.addr_int[(int)(res) * obj->img.width + (int)(res2 - 1 + obj->img.width)%obj->img.width];
	y2 = obj->bump.addr_int[(int)(res) * obj->img.width + (int)(res2 + 1 + obj->img.width)%obj->img.width];
	r2 = (y2 - y1)/0x0300000;
	// if (fabs(y1) > max)
	// 	max = fabs(y1);
	// if (fabs(y2) > max)
	// 	max = fabs(y2);
	// printf("%d\n", max);
	// printf("%d %d\n", (int)r1, (int)r2);
	// if (obj->img.sqsize)
	{
		bump_cal(r2,
			&obj->ref.j, &point->normal);
		bump_cal(r1,
			&obj->ref.k, &point->normal);
		point->normal = norm_c(point->normal);
	}
	return (point);
}

t_point	*checkerboard_sphere(t_point *point, t_obj *obj)
{
	double			res;
	double			res2;
	t_coordinates	x;

	x = prod_c(dot_prod_c(make_coor(0, 0, 1), point->normal),
			make_coor(0, 0, 1));
	x = norm_c(sub_c(point->normal, x));
	res = (point->point.z - obj->coor.z);
	res2 = (atan2(x.x, x.y) / (M_PI)) * obj->diameter;
	if ((int)(round(res) + round(res2)) % 2 == 0)
			point->color = obj->color2;
	return (point);
}

t_point	*creat_sphere_point(t_obj *obj, t_coordinates v, double t)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		err();
	point->distance = t;
	point->point = prod_c(t, v);
	point->normal = norm_c(sub_c(point->point, obj->coor));
	point->color = obj->color;
	obj->ref = creat_ref(point->normal);
	if (obj->id == 1)
		return (texture_sphere(point, obj));
	if (obj->id == 2)
		return (checkerboard_sphere(point, obj));
	return (point);
}

t_point	*intersection_sphere(t_coordinates v, t_obj *obj)
{
	t_quad_eq	parm;

	if (!obj || obj->type != 0)
		return (NULL);
	parm.a = dot_prod_c(v, v);
	parm.b = -2 * dot_prod_c(v, obj->coor);
	parm.c = dot_prod_c(obj->coor, obj->coor) - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta < EPSILON)
		return (NULL);
	return (creat_sphere_point(obj, v, parm.r1));
}
