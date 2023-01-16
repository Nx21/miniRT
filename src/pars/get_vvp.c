/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vvp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:13:54 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/15 15:07:46 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void    get_vvp(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	scene->cam_vec_x = norm_c(scene->cam_vec_x);
	scene->cam_vec_y = mak_cor(0,1,0);
	if (equalc(norm_c(scene->cam_vec_x), mak_cor(0,1,0)))
		scene->cam_vec_y = mak_cor(1,0,0);
	scene->cam_vec_z = norm_c(cross_prod_c(scene->cam_vec_x, scene->cam_vec_y));
	scene->cam_vec_y = norm_c(cross_prod_c(scene->cam_vec_z, scene->cam_vec_x));
	double angtopix = M_PI / (3 * WIDTH);
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			scene->cam[i][j] = norm_c(add_c(scene->cam_vec_x, add_c(prod_c(sin(i * angtopix - scene->fov/2), scene->cam_vec_y),prod_c(sin(j * angtopix - scene->fov/2), scene->cam_vec_z))));
		}
	}
}