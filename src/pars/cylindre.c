/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:04:42 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/23 01:28:06 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cylinder_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;
	t_obj	*obj;

	tmp = ft_split(line, ' ');
	if (ft_listlen(tmp) != 6 || ft_strcmp(tmp[0], "cy"))
		exit(1);
	obj = new_obj(2);
	obj->coor = ft_atoc(tmp[1]);
	obj->vec = ft_atoc(tmp[2]);
	obj->diameter = ft_atof(tmp[3]);
	obj->height = ft_atof(tmp[4]);
	obj->color = ft_atocolor(tmp[5]);
	scene->obj = add_back(scene->obj, obj);
	free(line);
	free_list(tmp);
	pars(scene, fd);
}