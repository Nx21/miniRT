/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orekabe <orekabe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:36:01 by orekabe           #+#    #+#             */
/*   Updated: 2023/02/09 17:48:42 by orekabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_init(t_scene *scene)
{
	int	i;

	i = -1;
	scene->ratio = -1;
	scene->fov = -1;
	scene->light = NULL;
	scene->obj = NULL;
	scene->v_cam = (t_coordinates **)malloc(WIDTH * sizeof(t_coordinates *));
	if (!scene->v_cam)
		err();
	while (++i < WIDTH)
	{
		scene->v_cam[i] = (t_coordinates *)malloc(HEIGHT
				* sizeof(t_coordinates));
		if (!scene->v_cam[i])
			err();
	}
}

void	change_referance(t_scene *scene)
{
	t_obj	*obj;
	t_light	*light;

	obj = scene->obj;
	while (obj)
	{
		obj->coor = sub_c(obj->coor, scene->cam_co);
		obj = obj->next;
	}
	light = scene->light;
	while (light)
	{
		light->light_co = sub_c(light->light_co, scene->cam_co);
		light = light->next;
	}
	scene->cam_co = sub_c(scene->cam_co, scene->cam_co);
}

void	brighting(t_scene *scene)
{
	t_light	*tmp;
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

int	main(int argc, char const *argv[])
{
	t_scene	scene;
	int		fd;

	if (argc != 2)
		return (1);
	if (!end_with((char *)argv[1], ".rt"))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	scene_init(&scene);
	pars(&scene, fd);
	get_v_cam(&scene);
	change_referance(&scene);
	scene.img.mlx = mlx_init();
	scene.img.mlx_win = mlx_new_window(scene.img.mlx, WIDTH, HEIGHT, "miniRT");
	scene.img.img = mlx_new_image(scene.img.mlx, WIDTH, HEIGHT);
	scene.img.addr = mlx_get_data_addr(scene.img.img, &scene.img.bits_per_pixel,
			&scene.img.line_length, &scene.img.endian);
	render(&scene);
	mlx_put_image_to_window(scene.img.mlx, scene.img.mlx_win,
		scene.img.img, 0, 0);
	ft_hook(&scene);
	mlx_loop(scene.img.mlx);
	return (0);
}
