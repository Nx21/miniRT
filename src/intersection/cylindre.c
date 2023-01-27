/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:21:29 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/26 17:24:39 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point *creat_point_cylindre(t_coordinates p, t_coordinates c, t_coordinates v)
{
	t_point *point;

	point = (t_point *)malloc(sizeof(t_point));
	point->point = p;
	point->normal = norm_c(sub_c(sub_c(p,c), v));
	return point;
}

t_point *intersection_cylindre_down(t_coordinates v, t_obj *obj)
{
	t_obj tmp;

	tmp = *obj;
	tmp.vec = sub_c(mak_cor(0,0,0), tmp.vec);
	return intersection_plan(v, &tmp);
}
t_point *intersection_cylindre_up(t_coordinates v, t_obj *obj)
{
	t_obj tmp;

	tmp = *obj;
	tmp.coor = add_c(tmp.coor,prod_c(tmp.height, tmp.vec));
	return intersection_plan(v, &tmp);
}

t_point	*get_point_cylindre(t_eqtpara parm, t_obj *obj, t_coordinates v)
{
	double m;
	t_point *p;

	m = dot_prod_c(v, obj->vec) * parm.r1 - dot_prod_c(obj->coor, obj->vec);
	if (m >= 0 && m <= obj->height)
	{
		p = creat_point_cylindre(prod_c(parm.r1, v), obj->coor, prod_c(m, obj->vec));
		p->color = obj->color;
		p->distance = parm.r1;
		return p;
	}
	else if (m < 0)
	{
		m = dot_prod_c(v, obj->vec) * parm.r2 - dot_prod_c(obj->coor, obj->vec);
		if(m < 0)
			return NULL;
		return intersection_cylindre_down(v, obj);;
	}
	m = dot_prod_c(v, obj->vec) * parm.r2 - dot_prod_c(obj->coor, obj->vec);
	if(m > obj->height)
		return NULL;
	return intersection_cylindre_up(v, obj);
}

t_point	*intersection_cylindre(t_coordinates v, t_obj *obj)
{
	t_eqtpara		parm;

	if(!obj || obj->type != 2)
		return NULL;
	parm.a = dot_prod_c(v,v) - pow(dot_prod_c(v,obj->vec), 2);
	parm.b = -2 * (dot_prod_c(v, obj->coor) - dot_prod_c(v, obj->vec) * dot_prod_c(obj->coor, obj->vec));
	parm.c = dot_prod_c(obj->coor, obj->coor) - pow(dot_prod_c(obj->coor, obj->vec), 2) - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta < 0)
		return (NULL);
	return	(get_point_cylindre(parm, obj, v));
}