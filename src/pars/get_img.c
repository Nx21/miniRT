/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:54:58 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/09 17:46:05 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_img(char *file, t_obj *obj)
{
	char	**str;
	int		fd;

	obj->id = 1;
	str = ft_split(file, ':');
	obj->img.mlx = mlx_init();
	if (ft_lstsize(str) != 3)
		err();
	fd = open(str[1], O_RDWR);
	if (fd == -1)
		err();
	close(fd);
	obj->img.sqsize = ft_atof(str[2]);
	obj->img.img = mlx_xpm_file_to_image(obj->img.mlx,
			str[1], &obj->img.width, &obj->img.height);
	if (!obj->img.img)
		exit(0);
	obj->img.addr_int = (int *)mlx_get_data_addr(obj->img.img,
			&obj->img.bits_per_pixel, &obj->img.line_length,
			&obj->img.endian);
	if (!obj->img.addr_int)
		err();
	free_list(str);
}
