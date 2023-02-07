/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperbol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:49 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/07 21:36:39 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cube_pars(char *line, t_scene *scene, int fd)
{
	char	**tmp;
	t_obj	*obj;

    puts("||");
	tmp = ft_split(line, ' ');
	if ((ft_lstsize(tmp) != 6 && ft_lstsize(tmp) != 7) || ft_strcmp(tmp[0], "hb"))
		exit(1);
	obj = new_obj(4);
	obj->coor = ft_atoc(tmp[1]);
	obj->vec = norm_c(ft_atoc(tmp[2]));
	obj->diameter = ft_atof(tmp[3]);
	obj->height = ft_atof(tmp[4]);
	if (start_with(tmp[5], "tx:") && !tmp[6])
		get_img(tmp[5], scene, obj);
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
    obj->ref = creat_ref(obj->vec);
	scene->obj = add_front(scene->obj, obj);


	
    free(line);
	free_list(tmp);
	pars(scene, fd);
}