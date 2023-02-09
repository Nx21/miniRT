/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:54:46 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 01:07:12 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_color color_degree(t_color color, double d)
{
	t_color res;
	
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
	if(res.b < 1)
		res.b = 0;
	if (res.b >= 255)
		res.b = 255;
	return res;
}
t_color add_color(t_color color1, t_color color2)
{
	t_color res;

	res.r = ((color1.r & 0xff )+ (color2.r & 0xff));
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
	if(res.b < 1)
		res.b = 0;
	if (res.b >= 255)
		res.b = 255;
	return res;
}
t_color prod_color(t_color color1, t_color color2)
{
	t_color res;

	res.r = ((color1.r & 0xff ) * (color2.r & 0xff)) /256;
	if (res.r > 255)
		res.r = 255; 
	if (res.r < 1)
		res.r = 0;
	res.g = ((color1.g & 0xff) * (color2.g & 0xff)) /256;
	if (res.g > 255)
		res.g = 255;
	if (res.g < 1)
		res.g = 0;
	res.b = ((color1.b & 0xff) * (color2.b & 0xff)) /256;
	if(res.b < 1)
		res.b = 0;
	if (res.b >= 255)
		res.b = 255;
	return res;
}

double is_intersection_sphere(t_coordinates x, t_coordinates v, t_obj *obj)
{
	t_quad_eq   parm;

	x = sub_c(obj->coor, x);
	if(!obj || obj->type != 0)
		return 0;
	parm.a = dot_prod_c(v,v);
	parm.b = -2 * dot_prod_c(v, x);
	parm.c = dot_prod_c(x, x)  - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta <= EPSILON || (parm.r1 <= EPSILON && parm.r2 <= EPSILON))
		return (0);
	if (parm.r1 >= -EPSILON)
		return parm.r1;
	if (parm.r2 >= -EPSILON)
		return parm.r1;
	return 0;
}

double is_intersection_cylindre(t_coordinates x, t_coordinates v, t_obj *obj)
{
	t_quad_eq		parm;

	if(!obj || obj->type != 2)
		return 0;
	x = sub_c(obj->coor, x);
	parm.a = dot_prod_c(v,v) - pow(dot_prod_c(v,obj->vec), 2);
	parm.b = -2 * (dot_prod_c(v, x) - dot_prod_c(v, obj->vec) * dot_prod_c(x, obj->vec));
	parm.c = dot_prod_c(x, x) - pow(dot_prod_c(x, obj->vec), 2) - pow(obj->diameter, 2);
	parm = sd_equation(parm);
	if (parm.delta < EPSILON || (parm.r1 <= EPSILON && parm.r2 <= EPSILON))
		return (0);
	double m = dot_prod_c(v, obj->vec) * parm.r1 - dot_prod_c(x, obj->vec);
	// double m2 = dot_prod_c(v, obj->vec) * parm.r2 - dot_prod_c(x, obj->vec);
	if (m >= 0 && m <= obj->height)
		return parm.r1;
	// if (m < 0 && m2 >= EPSILON)
	// 	return parm.r1;
	// if (m > obj->height && m2 <= obj->height)
	// 	return parm.r1;
	return 0;
}

double is_intersection_plan(t_coordinates x, t_coordinates v, t_obj *obj)
{
	double res,r1,r2;

	if(!obj)
		return 0;
	x = sub_c(obj->coor, x);
	r1 = dot_prod_c(v, obj->vec);
	r2 = dot_prod_c(x,obj->vec);
	if (r1 < EPSILON || r2 < EPSILON)
		return 0;
	res = r2/r1;
	if (res < EPSILON)
		return 0;
	return res;
}


double is_intersection_square(t_coordinates x, t_coordinates v, t_obj *obj)
{
	double res,r1,r2;
	t_coordinates tmp;
	t_coordinates y;

	if(!obj)
		return 0;
	y = x;
	x = sub_c(obj->coor, x);
	r1 = dot_prod_c(v, obj->vec);
	r2 = dot_prod_c(x,obj->vec);
	if (!r1 || !r2)
		return 0;
	res = r2/r1;
	if (res < EPSILON)
		return 0;
	tmp = sub_c(add_c(prod_c(res, v), y), obj->coor);
	if (fabs(dot_prod_c(tmp, obj->ref.j)) > obj->diameter  || fabs(dot_prod_c(tmp, obj->ref.k)) > obj->diameter)
		return (0);
	return res;
}

double is_intersection_circle(t_coordinates x, t_coordinates v, t_obj *obj)
{
	double res,r1,r2;
	t_coordinates tmp;
	t_coordinates y;

	if(!obj)
		return 0;
	y = x;
	x = sub_c(obj->coor, x);
	r1 = dot_prod_c(v, obj->vec);
	r2 = dot_prod_c(x,obj->vec);
	if (!r1 || !r2)
		return 0;
	res = r2/r1;
	if (res < EPSILON)
		return 0;
	tmp = sub_c(add_c(prod_c(res, v), y), obj->coor);
	if (dot_prod_c(tmp, tmp) > obj->diameter * obj->diameter)
		return (0);
	return res;
}

double	find_is_intersection(t_coordinates v, t_obj *obj, t_coordinates x)
{
	if(obj->type == 0)
		return is_intersection_sphere(x, v, obj);
	else if (obj->type == 1)
		return is_intersection_plan(x, v, obj);
	else if (obj->type == 2)
		return is_intersection_cylindre(x, v, obj);
	else if (obj->type == 3)
		return is_intersection_circle(x, v, obj);
	else if (obj->type == 4)
		return is_intersection_square(x, v, obj);
	return 0;
}

int is_intersected(t_scene scene, t_coordinates l, t_coordinates x)
{
	t_obj *obj;
	double tmp;
	double	maxdis;
	t_point *res;

	t_coordinates v = sub_c(l, x);
	maxdis = sqrt(dot_prod_c(v, v));
	v = norm_c(v);
	obj = scene.obj;
	res = NULL;
	tmp = 0;
	while(obj)
	{
		tmp = find_is_intersection(v, obj, x);
		if (tmp && tmp < maxdis)
			return (1);
		obj = obj->next;
	}
	return (0);
}


double is_light(t_point *p, t_light *l, t_coordinates v)
{
	t_coordinates vprinm;
	t_coordinates vlight;

	vprinm = norm_c(add_c(v, prod_c(-2 * dot_prod_c(p->normal, v), p->normal)));
	vlight = norm_c(sub_c(l->light_co, p->point));
	return pow(dot_prod_c(vprinm, vlight),25);
}



t_color	add_light(t_point *res, t_scene scene, t_coordinates v)
{
	t_color color;
	t_light *l;

	l = scene.light;
	color = ft_itocolor(0);
	while (l)
	{
		if(res && !is_intersected(scene, l->light_co, res->point))
		{
			color = add_color(color, (add_color(prod_color(l->light_color, color_degree(res->color, l->light_b * fabs(dot_prod_c(norm_c(sub_c(l->light_co, res->point)), res->normal))))
				,color_degree(l->light_color, l->light_b * is_light(res, l, v)))));
		}
		l = l->next;
	}
	if(res)
		return (add_color(color, color_degree(res->color, scene.ratio)));
	return ft_itocolor(0);
}

t_point	*find_intersection(t_coordinates v, t_obj *obj)
{
	if(obj->type == 0)
		return intersection_sphere(v, obj);
	else if (obj->type == 1)
		return intersection_infinit_plan(v, obj);
	else if (obj->type == 2)
		return intersection_cylindre(v, obj);
	else if (obj->type == 3)
		return intersection_circle(v, obj);
	else if (obj->type == 4)
		return intersection_square(v, obj);
	return NULL;
}


t_color	pixel_color(t_scene scene, int i, int j)
{
	t_obj *obj;
	t_point *tmp;
	t_point *res;

	res = NULL;
	tmp = NULL;
	obj = scene.obj;
	while(obj)
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
	return add_light(res, scene, scene.v_cam[i][j]);
}