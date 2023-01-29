/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:54:46 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/26 17:24:55 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int color_degree(int color, double d)
{
	int r,g,b;
	// int rndm = rand();
	// d = fabs(d);
	r = ((int)(((color >> 16) & 0xff) * d));
	if (r > 0xff)
		r = 0xff; 
	if (r < 0)
		r = 0;
	g = ((int)(((color >> 8) & 0xff) * d));
	if (g > 0xff)
		g = 0xff;
	if (g < 0)
		g = 0;
	b = ((int)(((color) & 0xff) * d));
	if(b < 0)
		b = 0;
	if (b >= 0xff)
		b = 0xff;
	return (r << 16) + (g << 8) + b;
}
int add_color(int color1, int color2)
{
	int r,g,b;
	r = ((int)(((color1 >> 16) & 0xff) + ((color2 >> 16) & 0xff)));
	if (r > 0xff)
		r = 0xff; 
	if (r < 0)
		r = 0;
	g = ((int)(((color1 >> 8) & 0xff) + ((color2 >> 8) & 0xff)));
	if (g > 0xff)
		g = 0xff;
	if (g < 0)
		g = 0;
	b = ((int)(((color1 >> 0) & 0xff) + ((color2 >> 0) & 0xff)));
	if(b < 0)
		b = 0;
	if (b >= 0xff)
		b = 0xff;
	return (r << 16) + (g << 8) + b;
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
	if (parm.delta < 0 || (parm.r1 <= EPSILON && parm.r2 <= EPSILON))
		return (0);
	if (parm.r1)
		return parm.r1;
	return parm.r2;
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
	if (parm.delta < 0 || (parm.r1 <= EPSILON && parm.r2 <= EPSILON))
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
		if(obj->type == 0)
			tmp = is_intersection_sphere(x, v, obj);
		// else if (obj->type == 1)
		// 	tmp = is_intersection_plan(x, v, obj);
		else if (obj->type == 2)
			tmp = is_intersection_cylindre(x, v, obj);
		// else
		// 	tmp = NULL;
		if (tmp && tmp <= maxdis)
			return (1);
		obj = obj->next;
	}
	return (0);
}


double is_light(t_point *p, t_light *l, t_coordinates v)
{
	t_coordinates vprinm = norm_c(add_c(v, prod_c(-2 * dot_prod_c(p->normal, v), p->normal)));
	t_coordinates vlight = norm_c(sub_c(l->light_co, p->point));
	 
	// if((dot_prod_c(vprinm, vlight)) > 0.9)
	return (pow(dot_prod_c(vprinm, vlight), 23)) * l->light_b;
	// return 0;
}

double is_light2(t_point *p, t_light *l, t_coordinates v)
{
	
	 
	// if((dot_prod_c(vprinm, vlight)) > 0.9)
	if (dot_prod_c(l->light_co, v) < dot_prod_c(p->point, v))
		return (pow(dot_prod_c(norm_c(l->light_co), v), 1));
	return 0;
}


int	pixel_color(t_scene scene, int i, int j)
{
	t_obj *obj;
	t_point *tmp;
	t_point *res;

	obj = scene.obj;
	res = NULL;
	tmp = NULL;
	while(obj)
	{
		if(obj->type == 0)
			tmp = intersection_sphere(scene.v_cam[i][j], obj);
		else if (obj->type == 1)
			tmp = intersection_plan(scene.v_cam[i][j], obj);
		else if (obj->type == 2)
			tmp = intersection_cylindre(scene.v_cam[i][j], obj);
		else
			tmp = NULL;
		if (tmp && (!res || res->distance > tmp->distance))
		{
			free(res);
			res = tmp;
		}
		else
			free(tmp);
		obj = obj->next;
	}
	// if(is_light(res, scene.light, scene.cam[i][j]))
	// {
	// 	return color_degree(0xffffff , );
	// }
	if(res && !is_intersected(scene, scene.light->light_co, res->point))
	{
		return add_color(color_degree(res->color, scene.ratio),
			add_color(color_degree(res->color, fabs(dot_prod_c(norm_c(sub_c(scene.light->light_co, res->point)), res->normal)))
			,color_degree(0xffffff, is_light(res, scene.light, scene.v_cam[i][j]))));
	}
	if(res)
		return color_degree(res->color, scene.ratio);
	return 0;
}