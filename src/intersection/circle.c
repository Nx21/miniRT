/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:47:56 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/30 04:57:08 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_point	*intersection_circle(t_coordinates v, t_obj *obj)
{
	t_point	*point;
	t_coordinates tmp;

	if(!obj || obj->type != 3)
		return NULL;
	point = intersection_plan(v, obj);
	if(!point)
		return NULL;
	tmp = sub_c(point->point, obj->coor);
	if (dot_prod_c(tmp, tmp) > (obj->diameter * obj->diameter))
		return (free(point), NULL);
	return point;
}