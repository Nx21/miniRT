/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:05:30 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 01:56:15 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	pars(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	line = ft_strtrim(line, "\n \t");
	if (!line)
		return ;
	if (ft_strcmp(line, "") == 0 || start_with(line, "#"))
		return (free(line), pars(scene, fd));
	if (start_with(line, "A"))
		return (ambient_pars(line, scene, fd));
	if (start_with(line, "C"))
		return (camera_pars(line, scene, fd));
	if (start_with(line, "L") || start_with(line, "l"))
		return (light_pars(line, scene, fd));
	if (start_with(line, "sp"))
		return (sphere_pars(line, scene, fd));
	if (start_with(line, "pl"))
		return (plane_pars(line, scene, fd));
	if (start_with(line, "cy"))
		return (cylinder_pars(line, scene, fd));
	if (start_with(line, "cb"))
		return (cube_pars(line, scene, fd));
	exit(1);
}