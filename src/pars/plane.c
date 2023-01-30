/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:06:21 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/30 03:49:04 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	plane_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;
	t_obj	*obj;

	tmp = ft_split(line, ' ');
	if (ft_listlen(tmp) != 4 || ft_strcmp(tmp[0], "pl"))
		exit(1);
	obj = new_obj(1);
	obj->coor = ft_atoc(tmp[1]);
	obj->vec = ft_atoc(tmp[2]);
	obj->color = ft_atocolor(tmp[3]);
	scene->obj = add_front(scene->obj, obj);
	free(line);
	free_list(tmp);
	pars(scene, fd);
}