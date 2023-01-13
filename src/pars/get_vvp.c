/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vvp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:13:54 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/13 19:17:19 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coordinates mak_cor(double x, double y, double z)
{
	t_coordinates res;

	res.x = x;
	res.y = y;
	res.z = z;
}

t_coordinates cross_prod_c(t_coordinates v, t_coordinates u)
{
	t_coordinates res;

	res.x = v.y * u.z - v.z * u.y;
	res.y = v.z * u.x - v.x * u.z;
	res.z = v.x * u.z - v.z * u.x;

	return res;
}

double doty_prod_c(t_coordinates v, t_coordinates u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}


t_coordinates add_c(t_coordinates v, t_coordinates u)
{
	return mak_cor(v.x + u.x, v.y + u.y, v.z + u.z);
}

t_coordinates sub_c(t_coordinates v, t_coordinates u)
{
	return mak_cor(v.x - u.x, v.y - u.y, v.z -u.z);
}


void    get_vvp(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	scene->cam_vec_y = mak_cor(0,1,0);
	if (equalc(scene->cam_vec_x, mak_cor(0,1,0)))
		scene->cam_vec_y = mak_cor(1,0,0);
	scene->cam_vec_z = cross_prod_c(scene->cam_vec_x, scene->cam_vec_y);
	scene->cam_vec_y = cross_prod_c(scene->cam_vec_z, scene->cam_vec_x);
	
}