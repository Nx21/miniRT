/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhanafi <nhanafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:51:17 by nhanafi           #+#    #+#             */
/*   Updated: 2023/01/22 01:09:09 by nhanafi          ###   ########.fr       */
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

t_resobj	*resobj(t_obj	*obj, double distance)
{
	t_resobj *res;

	res = malloc(sizeof(t_resobj));
	res->distance = distance;
	res->obj = obj;
	return res;
}

t_resobj	*intersection_sphere(t_scene scene, int  i, int j, t_obj *obj)
{
	t_coordinates x = scene.cam_co;
	t_coordinates v = scene.cam[i][j];
	double delta,r1,r2;

	if(!obj || obj->type != 0)
		return NULL;
	double a = doty_prod_c(v,v);
	double b = 2 * doty_prod_c(v, sub_c(x, obj->coor));
	double c = doty_prod_c(obj->coor, obj->coor) + doty_prod_c(x,x) - 2 * doty_prod_c(x,obj->coor) - pow(obj->diameter, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (NULL);
	r1 = (-b - sqrt(delta)) / (2 * a);
	r2 = (-b + sqrt(delta)) / (2 * a);
	if ((r1 < 0 || r1 > r2) && r2 >= 0)
		return (resobj(obj, r2));
	if (r1 < 0)
		return NULL;
	return (resobj(obj, r1));
}

t_resobj	*intersection_plan(t_scene scene, int  i, int j, t_obj *obj)
{
	t_coordinates x = scene.cam_co;
	t_coordinates v = scene.cam[i][j];
	double res,r1,r2;

	if(!obj || obj->type != 1)
		return NULL;
	r1 = doty_prod_c(v, obj->vec);
	if (!r1)
		return NULL;
	r2 = doty_prod_c(sub_c(obj->coor, x) ,obj->vec);
	if (!r1 && r2)
		return resobj(obj, 0);
	res = r2/r1;
	if (res < 0)
		return NULL;
	return (resobj(obj, res));
}

int	pixel_color(t_scene scene, int i, int j)
{
	t_obj *obj;
	t_resobj *tmp;
	t_resobj *res;

	obj = scene.obj;
	res = NULL;
	tmp = NULL;
	while(obj)
	{
		if(obj->type == 0)
			tmp = intersection_sphere(scene, i, j, obj);
		else if (obj->type == 1)
			tmp = intersection_plan(scene, i, j, obj);
		else
			tmp = NULL;
		if (tmp && (!res || res->distance > tmp->distance))
		{
			free(res);
			res = tmp;
		}
		else
			free(tmp);
		obj = obj->next;
	}
	if(res)
		return res->obj->color;
	return 0;
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

	printf("%d", scene.obj->type);
	printc(scene.obj->coor);
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
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return 0;
}
