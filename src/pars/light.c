/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:05:01 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/01 15:06:17 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*new_light(t_light *next)
{
	t_light *light;

	light = (t_light *) malloc(sizeof(t_light));
	light->next = next;
	return (light);
}


void	light_pars(char *line, t_scene *scene, int fd)
{
	char **tmp;
	t_light	*light;

	
	tmp = ft_split(line, ' ');
	if (ft_lstsize(tmp) != 4 || ft_strcmp(tmp[0], "l"))
		exit(1);
	light = new_light(scene->light);
	light->light_co = ft_atoc(tmp[1]);
	light->light_b = ft_atof(tmp[2]);
	light->light_color = ft_atocolor(tmp[3]);
	light->light_color = color_degree(light->light_color, light->light_b);
	if (light->light_b < 0 || light->light_b > 1)
		exit(1);
	free(line);
	free_list(tmp);
	scene->light = light;
	pars(scene, fd);
}
