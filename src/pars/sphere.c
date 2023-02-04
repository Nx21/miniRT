/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:06:44 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/04 17:37:09 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;
	t_obj	*obj;

	tmp = ft_split(line, ' ');
	if ((ft_lstsize(tmp) != 4 &&  ft_lstsize(tmp) != 5)|| ft_strcmp(tmp[0], "sp"))
		exit(1);
	obj = new_obj(0);
	obj->coor = ft_atoc(tmp[1]);
	obj->diameter = ft_atof(tmp[2]);
	if (start_with(tmp[3], "tx:") && !tmp[4])
		get_img(tmp[3], scene, obj);
	else
	{
		obj->color = ft_atocolor(tmp[3]);
		obj->color2 = obj->color;
		if (tmp[4])
			obj->color2 = ft_atocolor(tmp[4]);
	}
	scene->obj = add_front(scene->obj, obj);
	free(line);
	free_list(tmp);
	pars(scene, fd);
}
