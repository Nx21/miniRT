/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:51:17 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/25 11:09:21 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_init(t_scene *scene)
{
	scene->ambientcolor = -1;
	scene->fov = -1;
	scene->light = NULL;
	scene->obj = NULL;
	scene->cam = (t_coordinates **)malloc(WIDTH * sizeof(t_coordinates *));
	for (size_t i = 0; i < WIDTH; i++)
	{
		scene->cam[i] = (t_coordinates *)malloc(HEIGHT * sizeof(t_coordinates));
	}
	
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	change_referance(t_scene *scene)
{
	t_obj *obj;
	t_light *light;

	obj = scene->obj;
	while (obj)
	{
		obj->coor = sub_c(obj->coor, scene->cam_co);
		obj = obj->next;
	}
	light = scene->light;
	while(light)
	{
		light->light_co = sub_c(light->light_co, scene->cam_co);
		light = light->next;
	}
	scene->cam_co = sub_c(scene->cam_co, scene->cam_co);
}

int main(int argc, char const *argv[])
{
	t_scene	scene;
	int		fd;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	if (argc != 2)
		return 1;
	if (!end_with((char *)argv[1], ".rt"))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		return (1);
	scene_init(&scene);
	pars(&scene, fd);
	get_vvp(&scene);
	change_referance(&scene);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			my_mlx_pixel_put(&img, i, j, pixel_color(scene, i, j));
			// pixel_color(scene, i, j);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return 0;
}
