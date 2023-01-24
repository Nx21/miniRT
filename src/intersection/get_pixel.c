/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:54:46 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/24 06:26:21 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int color_degree(int color, double d)
{
	int r,g,b;
	r = ((int)(((color >> 16) & 0xff) * d));
	if (r < 0)
		r = 0;
	g = ((int)(((color >> 8) & 0xff) * d));
	if (g < 0)
		g = 0;
	b = ((int)(((color) & 0xff) * d));
	if(b < 0)
		b = 0;
	return (r << 16) + (g << 8) + b;
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
			tmp = intersection_sphere(scene.cam[i][j], obj);
		else if (obj->type == 1)
			tmp = intersection_plan(scene.cam[i][j], obj);
		else if (obj->type == 2)
			tmp = intersection_cylindre(scene.cam[i][j], obj);
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
	if(res)
	{
		// return res->color;
		// printf("%f   ", dot_prod_c(norm_c(sub_c(scene.light->light_co, res->point)), res->normal));
		return  color_degree(res->color, dot_prod_c(norm_c(sub_c(scene.light->light_co, res->point)), res->normal));
	}
	return 0;
}