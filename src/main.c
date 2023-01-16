/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:51:17 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/15 17:52:22 by nhanafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_init(t_scene *scene)
{
	scene->ambientcolor = -1;
	scene->fov = -1;
	scene->light_color = -1;
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


double intersection(t_scene scene, int  i, int j)
{
	t_obj *obj = scene.obj;
	t_coordinates x = scene.cam_co;
	t_coordinates v = scene.cam[i][j];
	double res,r1,r2;

	if(!obj || obj->type != 0)
		return 0;
	double a = dist_sqv(v);
	double b = 2 * (v.x * (x.x - obj->coor.x) +v.y * (x.y - obj->coor.y) +v.z * (x.z - obj->coor.z));
	double c = dist_sqv(obj->coor) + dist_sqv(x) - 2 * (obj->coor.x * x.x + obj->coor.y * x.y + obj->coor.z * x.z) - pow(obj->diameter, 2);
	res = pow(b, 2) - 4 * a * c;
	if(res < 0)
		return (res);
	r1 = (-b-sqrt(res))/2;
	r2 = (-b+sqrt(res))/2;
	res = r1;
	if (res > r2)
		res = r2;
	return (sqrt(dist_sqv(prod_c(res, v))));
	
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
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			my_mlx_pixel_put(&img, i, j, 0x00000000);
			int res = intersection(scene, i ,j);
			if (res >= 0)
				my_mlx_pixel_put(&img, i, j, 0x00ff0000 );
		}
		
	}
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return 0;
}
