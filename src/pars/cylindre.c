/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:04:42 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/06 13:45:40 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"




void	cylinder_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;
	t_obj	*obj;
	t_obj	*newobj;

	tmp = ft_split(line, ' ');
	if ((ft_lstsize(tmp) != 6 && ft_lstsize(tmp) != 7) || ft_strcmp(tmp[0], "cy"))
		exit(1);
	obj = new_obj(2);
	obj->coor = ft_atoc(tmp[1]);
	obj->vec = norm_c(ft_atoc(tmp[2]));
	obj->diameter = ft_atof(tmp[3]);
	obj->height = ft_atof(tmp[4]);
	if (start_with(tmp[5], "tx:") && !tmp[6])
		get_img(tmp[5], scene, obj);
	else
	{
		
		obj->color = ft_atocolor(tmp[5]);
		obj->color2 = obj->color;
		if (tmp[6])
			obj->color2 = ft_atocolor(tmp[6]);
	}
	scene->obj = add_front(scene->obj, obj);
	
	newobj = new_obj(3);
	newobj->img = obj->img;
	newobj->id = obj->id;
	newobj->color = obj->color;
	newobj->color2 = obj->color2;
	newobj->diameter = obj->diameter;
	newobj->vec = obj->vec;
	newobj->coor = obj->coor;
	scene->obj = add_front(scene->obj, newobj);
	
	newobj = new_obj(3);
	newobj->img = obj->img;
	newobj->id = obj->id;
	newobj->color = obj->color;
	newobj->color2 = obj->color2;
	newobj->diameter = obj->diameter;
	newobj->vec = obj->vec;
	newobj->coor = add_c(obj->coor, prod_c(obj->height, obj->vec));
	scene->obj = add_front(scene->obj, newobj);
	
	free(line);
	free_list(tmp);
	pars(scene, fd);
}