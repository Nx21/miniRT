/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:05:30 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/29 05:12:41 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void printc(t_coordinates c)
{
	printf("\t%f,%f,%f", c.x,c.y,c.z);
}


void	pars(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	line = ft_strtrim(line, "\n \t");
	if (!line)
		return ;
	if (ft_strcmp(line, "") == 0)
		return (free(line), pars(scene, fd));
	if (start_with(line, "A"))
		return (ambient_pars(line, scene, fd));
	if (start_with(line, "C"))
		return (camera_pars(line, scene, fd));
	if (start_with(line, "L"))
		return (light_pars(line, scene, fd));
	if (start_with(line, "sp"))
		return (sphere_pars(line, scene, fd));
	if (start_with(line, "pl"))
		return (plane_pars(line, scene, fd));
	if (start_with(line, "cy"))
		return (cylinder_pars(line, scene, fd));
	exit(1);
}