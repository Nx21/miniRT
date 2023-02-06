/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:21:29 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/06 14:49:39 by nhanafi          ###   ########.fr       */
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

// t_point *intersection_cylindre_down(t_coordinates v, t_obj *obj)
// {
// 	t_obj tmp;

// 	tmp = *obj;
// 	tmp.vec = sub_c(make_coor(0,0,0), tmp.vec);
// 	return intersection_plan(v, &tmp);
// }
// t_point *intersection_cylindre_up(t_coordinates v, t_obj *obj)
// {
// 	t_obj tmp;

// 	tmp = *obj;
// 	tmp.coor = add_c(tmp.coor,prod_c(tmp.height, tmp.vec));
// 	return intersection_plan(v, &tmp);
// }

t_point	*get_point_cylindre(t_quad_eq parm, t_obj *obj, t_coordinates v)
{
	double m;
	t_point *point;

	m = dot_prod_c(v, obj->vec) * parm.r1 - dot_prod_c(obj->coor, obj->vec);
	if (m >= 0 && m <= obj->height)
	{
		point = creat_point_cylindre(prod_c(parm.r1, v), obj->coor, prod_c(m, obj->vec));
		point->color = ft_itocolor(0xff);
		if(obj->id)
		{
			int res =0, res2 = 0;
			t_ref	ref;
			res = ((dot_prod_c(point->point, obj->vec)/obj->height) * obj->img.height/2);
			// x = point->normal;
			// res = atan(x.z/x.x) * 10 / M_PI;
			ref = creat_ref(obj->vec);
			t_coordinates x = prod_c(dot_prod_c(ref.i, point->normal),  ref.i);
			// printc(point->normal);
			x = norm_c(sub_c(point->normal, x));
			res2 = (1 - atan2(dot_prod_c(ref.j, x), dot_prod_c(ref.k, x))/M_PI) * obj->img.width;
			point->color = ft_itocolor(obj->img.addr_int[(int)(res) * obj->img.width + (int)(res2)]);
			double res3 = 0, res4 = 0;
			res3 = ((dot_prod_c(point->point, obj->vec)) * 100 / obj->height);
			res4 = (1 + atan2(dot_prod_c(ref.k, x), dot_prod_c(ref.j, x))/M_PI *100);
			point->normal = norm_c(add_c(point->normal, prod_c((round(res3) - res3) + (double)(rand()%110 - 50)/1000 ,ref.j)));
			point->normal = norm_c(add_c(point->normal, prod_c((round(res4) - res4)+(double)(rand()%110 - 50)/1000,ref.k)));
		
			point->point = prod_c(parm.r1 -  fabs(round(res3) - res3) - fabs(round(res4) - res4), v);
			// if ((int)(res + res2) % 2 == 0)
				// point->color = obj->color;
			// else
			// 	point->color = obj->color2;
		}
		point->distance = parm.r1;
		return point;
	}
	return NULL;
// 	else if (m < 0)
// 	{
// 		m = dot_prod_c(v, obj->vec) * parm.r2 - dot_prod_c(obj->coor, obj->vec);
// 		if(m < 0)
// 			return NULL;
// 		return intersection_cylindre_down(v, obj);;
// 	}
// 	m = dot_prod_c(v, obj->vec) * parm.r2 - dot_prod_c(obj->coor, obj->vec);
// 	if(m > obj->height)
// 		return NULL;
// 	return intersection_cylindre_up(v, obj);
}

t_point	*intersection_cylindre(t_coordinates v, t_obj *obj)
{
	t_quad_eq		parm;

	// exit(0);
	if(!obj || obj->type != 2)
		return NULL;
	parm.a = dot_prod_c(v,v) - pow(dot_prod_c(v,obj->vec), 2);
	parm.b = -2 * (dot_prod_c(v, obj->coor) - dot_prod_c(v, obj->vec) * dot_prod_c(obj->coor, obj->vec));
	parm.c = dot_prod_c(obj->coor, obj->coor) - pow(dot_prod_c(obj->coor, obj->vec), 2) - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta < EPSILON)
		return (NULL);
	return	(get_point_cylindre(parm, obj, v));
}