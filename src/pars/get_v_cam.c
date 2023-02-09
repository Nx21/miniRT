/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_v_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:13:54 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 05:31:11 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_v_cam(t_scene *scene)
{
	int		i;
	int		j;
	t_ref	ref;
	double	angtopix;

	i = 0;
	ref = creat_ref(scene->cam_vec_x);
	scene->cam_vec_x = norm_c(scene->cam_vec_x);
	angtopix = (M_PI * scene->fov) / (180 * WIDTH);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			scene->v_cam[i][j] = norm_c(add_c(ref.i,
						add_c(prod_c(sin(((double)(i - (WIDTH) / 2)
										*angtopix)),
								ref.j), prod_c(sin((double)(HEIGHT / 2 - j)
									*angtopix), ref.k))));
			j++;
		}
		i++;
	}
}
