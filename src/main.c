/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:51:17 by nhanafi           #+#    #+#             */
/*   Updated: 2023/02/08 12:37:24 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_close(t_scene *scene)
{
	mlx_destroy_image(scene->img.mlx, scene->img.img);
	mlx_destroy_window(scene->img.mlx, scene->img.mlx_win);
	exit (0);
}

int	ft_keys(int key, t_scene *scene)
{
	if (key == 53)
		ft_close(scene);
	return (0);
}

int	ft_destroy(t_scene *scene)
{
	mlx_destroy_image(scene->img.mlx, scene->img.img);
	mlx_destroy_window(scene->img.mlx, scene->img.mlx_win);
	exit (0);
}

void	ft_hook(t_scene *scene)
{
	mlx_hook(scene->img.mlx_win, 2, 0, ft_keys, scene);
	mlx_hook(scene->img.mlx_win, 17, 0, ft_destroy, scene);
}

void	scene_init(t_scene *scene)
{
	scene->ratio = -1;
	scene->fov = -1;
	scene->light = NULL;
	scene->obj = NULL;
	scene->v_cam = (t_coordinates **)malloc(WIDTH * sizeof(t_coordinates *));
	for (size_t i = 0; i < WIDTH; i++)
	{
		scene->v_cam[i] = (t_coordinates *)malloc(HEIGHT * sizeof(t_coordinates));
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


void brighting(t_scene *scene)
{
	t_light *tmp;
	double	sum;

	tmp = scene->light;
	sum = 0;
	while (tmp)
	{
		sum++;
		tmp = tmp->next;
	}
	tmp = scene->light;
	while (tmp)
	{
		tmp->light_b /= sum;
		tmp = tmp->next;
	}
}

int main(int argc, char const *argv[])
{
	t_scene	scene;
	int		fd;


	if (argc != 2)
		return 1;
	if (!end_with((char *)argv[1], ".rt"))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
		return (1);
	scene_init(&scene);
	pars(&scene, fd);
	get_v_cam(&scene);
	change_referance(&scene);
	scene.img.mlx = mlx_init();
	scene.img.mlx_win = mlx_new_window(scene.img.mlx, WIDTH, HEIGHT, "miniRT");
	scene.img.img = mlx_new_image(scene.img.mlx, WIDTH, HEIGHT);
	scene.img.addr = mlx_get_data_addr(scene.img.img, &scene.img.bits_per_pixel, &scene.img.line_length,
								&scene.img.endian);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			my_mlx_pixel_put(&scene.img, i, j, ft_colortoi(pixel_color(scene, i, j)));
		}
	}
	exit(0);
	ft_hook(&scene);
	mlx_put_image_to_window(scene.img.mlx, scene.img.mlx_win, scene.img.img, 0, 0);
	mlx_loop(scene.img.mlx);
	return 0;
}
