/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:03:57 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (scene->fov >= 0 || ft_lstsize(tmp) != 4 || ft_strcmp(tmp[0], "C"))
		err();
	scene->cam_co = ft_atoc(tmp[1]);
	scene->cam_vec_x = ft_atoc(tmp[2]);
	scene->fov = ft_atof(tmp[3]);
	if (scene->fov < 0 || scene->fov > 180)
		err();
	if (fabs(scene->cam_vec_x.x) > 1
		|| fabs(scene->cam_vec_x.y) > 1 || fabs(scene->cam_vec_x.z) > 1)
		err();
	free(line);
	free_list(tmp);
	pars(scene, fd);
}
