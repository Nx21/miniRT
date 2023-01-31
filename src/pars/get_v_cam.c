/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_v_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:13:54 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/30 01:11:37 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void    get_v_cam(t_scene *scene)
{
	int		i;
	int		j;
	t_ref	ref;

	i = 0;
	// printc(scene->cam_vec_x);
	ref = creat_ref(scene->cam_vec_x);
	scene->cam_vec_x = norm_c(scene->cam_vec_x);
	double angtopix = (M_PI * scene->fov) / (180 * WIDTH);
	for (i = 0; i < WIDTH; i++)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			scene->v_cam[i][j] = norm_c(add_c(ref.i, add_c(prod_c(sin(((double)(i - WIDTH/2) * angtopix)), ref.j),prod_c(sin((double)(HEIGHT/2 - j) * angtopix), ref.k))));
		}
	}
}