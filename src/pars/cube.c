/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:49 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap_ref(t_ref	*ref, int direction)
{
	t_coordinates	tmp;
	int				i;

	i = 1;
	while (i < abs(direction))
	{
		tmp = ref->i;
		ref->i = ref->j;
		ref->j = ref->k;
		ref->k = tmp;
		i++;
	}
	if (direction < 0)
	{
		ref->i = prod_c(-1, ref->i);
		ref->j = prod_c(-1, ref->j);
		ref->k = prod_c(-1, ref->k);
	}
}

void	creat_square(t_obj *sq, t_scene *scene, int direction)
{
	t_obj			*obj;
	t_coordinates	tmp;

	if (!direction)
		return ;
	obj = new_obj(4);
	*obj = *sq;
	swap_ref(&obj->ref, direction);
	obj->vec = obj->ref.i;
	tmp = prod_c(obj->diameter, obj->vec);
	obj->coor = add_c(tmp, obj->coor);
	scene->obj = add_front(scene->obj, obj);
}

void	cube_(char **tmp, t_obj *obj)
{
	obj->coor = ft_atoc(tmp[1]);
	obj->vec = ft_atoc(tmp[2]);
	obj->vec = norm_c(obj->vec);
	obj->diameter = ft_atof(tmp[3]);
	if (start_with(tmp[4], "tx:") && !tmp[5])
		get_img(tmp[4], obj);
	else
	{
		obj->id = 0;
		obj->color = ft_atocolor(tmp[4]);
		obj->color2 = obj->color;
		if (tmp[5])
		{
			obj->id = 2;
			obj->color2 = ft_atocolor(tmp[5]);
		}
	}
	obj->ref = creat_ref(obj->vec);
}

void	cube_pars(char *line, t_scene *scene, int fd)
{
	int		i;
	char	**tmp;
	t_obj	*obj;

	tmp = ft_split(line, ' ');
	if ((ft_lstsize(tmp) != 6 && ft_lstsize(tmp) != 5)
		|| ft_strcmp(tmp[0], "cb"))
		err();
	obj = new_obj(4);
	cube_(tmp, obj);
	i = -3;
	while (i < 4)
		creat_square(obj, scene, i++);
	free(obj);
	free(line);
	free_list(tmp);
	pars(scene, fd);
}
