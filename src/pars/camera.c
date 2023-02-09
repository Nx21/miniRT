/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:03:57 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/08 22:40:17 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_pars(char *line, t_scene *scene, int fd)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	if (scene->fov >= 0 || ft_lstsize(tmp) != 4 || ft_strcmp(tmp[0], "C"))
		exit(1);
	scene->cam_co = ft_atoc(tmp[1]);
	scene->cam_vec_x = ft_atoc(tmp[2]);
	scene->fov = ft_atof(tmp[3]);
	if (scene->fov < 0 || scene->fov > 180)
		exit(1);
	if (fabs(scene->cam_vec_x.x) > 1 || fabs(scene->cam_vec_x.y) > 1 || fabs(scene->cam_vec_x.z) > 1)
		exit(1);
	free(line);
	free_list(tmp);
	pars(scene, fd);
}
