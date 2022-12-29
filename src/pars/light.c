/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:05:01 by nhanafi           #+#    #+#             */
/*   Updated: 2022/12/29 05:12:19 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_pars(char *line, t_scene *scene, int fd)
{
	char **tmp;

	tmp = ft_split(line, ' ');
	if (scene->light_color >= 0 || ft_listlen(tmp) != 4 || ft_strcmp(tmp[0], "L"))
		exit(1);
	scene->light_co = ft_atoc(tmp[1]);
	scene->light_b = ft_atof(tmp[2]);
	scene->light_color = ft_atocolor(tmp[3]);
	if (scene->light_b < 0 || scene->light_b > 1)
		exit(1);
	free(line);
	free_list(tmp);
	printf("camera : %f\t%d\t", scene->light_b, scene->light_color);
	printc(scene->light_co);
	printf("\n");
	pars(scene, fd);
}
