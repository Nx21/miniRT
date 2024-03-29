/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:04:42 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	creat_circle(t_scene *scene, t_obj *obj, int i)
{
	t_obj			*newobj;
	t_coordinates	tmp;

	newobj = new_obj(3);
	newobj->img = obj->img;
	newobj->id = obj->id;
	newobj->color = obj->color;
	newobj->color2 = obj->color2;
	newobj->diameter = obj->diameter;
	newobj->vec = obj->vec;
	newobj->ref = obj->ref;
	tmp = prod_c(obj->height * i, obj->vec);
	newobj->coor = add_c(obj->coor, tmp);
	scene->obj = add_front(scene->obj, newobj);
}

void	creat_cylindre(t_obj *obj, char **tmp)
{
	obj->coor = ft_atoc(tmp[1]);
	obj->vec = norm_c(ft_atoc(tmp[2]));
	obj->diameter = ft_atof(tmp[3]);
	obj->height = ft_atof(tmp[4]);
	if (start_with(tmp[5], "tx:") && !tmp[6])
		get_img(tmp[5], obj);
	else
	{
		obj->id = 0;
		obj->color = ft_atocolor(tmp[5]);
		obj->color2 = obj->color;
		if (tmp[6])
		{
			obj->id = 2;
			obj->color2 = ft_atocolor(tmp[6]);
		}
	}
}

void	cylinder_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;
	t_obj	*obj;

	tmp = ft_split(line, ' ');
	if ((ft_lstsize(tmp) != 6 && ft_lstsize(tmp) != 7)
		|| ft_strcmp(tmp[0], "cy"))
		err();
	obj = new_obj(2);
	creat_cylindre(obj, tmp);
	obj->ref = creat_ref(obj->vec);
	scene->obj = add_front(scene->obj, obj);
	creat_circle(scene, obj, 0);
	creat_circle(scene, obj, 1);
	free(line);
	free_list(tmp);
	pars(scene, fd);
}
