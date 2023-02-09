/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 05:06:21 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	plane_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;
	t_obj	*obj;

	tmp = ft_split(line, ' ');
	if ((ft_lstsize(tmp) != 4 && ft_lstsize(tmp) != 5)
		|| ft_strcmp(tmp[0], "pl"))
		err();
	obj = new_obj(1);
	obj->coor = ft_atoc(tmp[1]);
	obj->vec = ft_atoc(tmp[2]);
	if (start_with(tmp[3], "tx:") && !tmp[4])
		get_img(tmp[3], obj);
	else
	{
		obj->color = ft_atocolor(tmp[3]);
		obj->color2 = obj->color;
		if (tmp[4])
		{
			obj->color2 = ft_atocolor(tmp[4]);
			obj->id = 2;
		}
	}
	obj->ref = creat_ref(obj->vec);
	scene->obj = add_front(scene->obj, obj);
	return (free(line), free_list(tmp), pars(scene, fd));
}
