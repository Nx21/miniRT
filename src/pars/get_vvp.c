/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vvp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:13:54 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/22 00:17:55 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void    get_vvp(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	// printc(scene->cam_vec_x);
	scene->cam_vec_x = norm_c(scene->cam_vec_x);
	// printc(scene->cam_vec_x);
	scene->cam_vec_y = mak_cor(0,1,0);
	if (equalc(norm_c(scene->cam_vec_x), mak_cor(0,1,0)))
		scene->cam_vec_y = mak_cor(1,0,0);
	scene->cam_vec_z = norm_c(cross_prod_c(scene->cam_vec_x, scene->cam_vec_y));
	scene->cam_vec_y = norm_c(cross_prod_c(scene->cam_vec_z, scene->cam_vec_x));
	double angtopix = (M_PI * scene->fov) / (180 * WIDTH);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			scene->cam[i][j] = norm_c(add_c(scene->cam_vec_x, add_c(prod_c(sin(((double)(i - WIDTH/2) * angtopix)), scene->cam_vec_y),prod_c(sin((double)(HEIGHT/2 - j) * angtopix), scene->cam_vec_z))));
		}
	}
}