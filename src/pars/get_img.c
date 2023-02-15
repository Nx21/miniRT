/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:54:58 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/14 18:57:19 by nhanafi          ###   ########.fr       */
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
	if (!end_with(str[2], ".xpm"))
		obj->img.sqsize = ft_atof(str[2]);
	else
	{
		obj->bump.mlx = mlx_init();
		obj->bump.img = mlx_xpm_file_to_image(obj->bump.mlx,
				str[2], &obj->bump.width, &obj->bump.height);
		if (!obj->bump.img)
		{
			printf("here");	
			exit(0);
		}
		obj->bump.addr_int = (int *)mlx_get_data_addr(obj->bump.img,
				&obj->bump.bits_per_pixel, &obj->bump.line_length,
				&obj->bump.endian);
		if (!obj->bump.addr_int)
			err();
	}
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
