/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperbol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:40:06 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/07 21:35:19 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point *creat_point_hyperbol(t_quad_eq parm, t_obj *obj, t_coordinates v, t_coordinates u)
{
	t_point *point;
	
	(void)u;
	(void)v;
	point = (t_point *)malloc(sizeof(t_point));
	point->point = prod_c(parm.r1, u);
	if (obj->diameter * pow(point->point.x - obj->coor.x, 2) + obj->height * pow(point->point.y - obj->coor.y, 2) > 10)
		return (free(point),NULL);
	point->normal = obj->vec;
	point->normal.x = 2 * obj->diameter * (point->point.x - obj->coor.x);
	point->normal.y = -2 * obj->height * (point->point.y - obj->coor.y);
	point->normal.z = -1;
	point->color = obj->color;
	return point;
}

t_point	*get_point_hyperbol(t_quad_eq parm, t_obj *obj, t_coordinates v, t_coordinates u)
{
	t_point *point;

	point = creat_point_hyperbol(parm, obj, v, u);
	return point;
}


t_point	*intersection_hyperbol(t_coordinates v, t_obj *obj)
{
	t_quad_eq		parm;
	t_coordinates	u;
	t_coordinates	c;

	if(!obj || obj->type != 4)
		return NULL;
	
	// u = v;
	c.z = dot_prod_c(obj->coor, obj->ref.i);
	c.x = dot_prod_c(obj->coor, obj->ref.j);
	c.y = dot_prod_c(obj->coor, obj->ref.k);
	u.z = dot_prod_c(v, obj->ref.i);
	u.x = dot_prod_c(v, obj->ref.j);
	u.y = dot_prod_c(v, obj->ref.k);
	
	parm.a = obj->diameter * pow(u.x,2) - obj->height * pow(u.y, 2);
	parm.b = 2 * (obj->height * u.y * c.y - obj->diameter * u.x * c.x) - u.z;
	parm.c = obj->diameter * pow(c.x, 2) + c.z - obj->height * pow(c.y,2);
	parm = sd_equation(parm);
	// puts("||");
	if (parm.delta < -EPSILON)
		return (NULL);
	return	(get_point_hyperbol(parm, obj, v, u));
}