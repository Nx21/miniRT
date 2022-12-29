/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:02:28 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/29 05:12:27 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ambient_pars(char *line, t_scene *scene, int fd)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	if (scene->ambientcolor >= 0 || ft_listlen(tmp) != 3 || ft_strcmp(tmp[0], "A"))
		exit(1);
	scene->ratio = ft_atof(tmp[1]);
	scene->ambientcolor = ft_atocolor(tmp[2]);
	if (scene->ratio < 0 || scene->ratio > 1)
		exit(1);
	free(line);
	free_list(tmp);
	pars(scene, fd);
}